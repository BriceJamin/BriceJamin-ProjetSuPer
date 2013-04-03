#include <QThread>

#include "tcpclientmanager.h"

TcpClientManager::TcpClientManager(int socketDescriptor, QTcpServer *parent) :
    QTcpSocket(parent), _socketDescriptor(socketDescriptor)
{
    connect(this, SIGNAL(error(SocketError)),
            this, SLOT(slot_tcpError()));
    connect(this, SIGNAL(connected()),
            this, SLOT(slot_connected()));
    connect(this, SIGNAL(disconnected()),
            this, SLOT(slot_disconnected()));
    connect(this, SIGNAL(sig_finished()),
            this, SLOT(deleteLater()));
}

void TcpClientManager::manage()
    // Slot appelé par started() lors de l'exécution d'un nouveau thread
{
    // Récupère le QTcpSocket du client à l'aide de son descripteur
    if(! setSocketDescriptor(_socketDescriptor) )
    {
        emit sig_finished();
        return;
    }

    // TODO : Signaler intruderEjected si ce n'est pas un reader puis quitter
    QString clientAddress = peerAddress().toString();
    if(bddisNotAReaderAddress(clientAddress))
    {
        abort();
        emit sig_intruderEjected(clientAddress);
        emit sig_finished();
        return;
    }

    Reader* reader = bddgetReaderByAddress(clientAddress);
    reader->isConnected(true);
    bddsetReader(reader);
    emit sig_readerConnected();
    // TODO : Signaler readerDetected si c'est un reader
    // emit sig_readerConnected(Reader*);
}

void TcpClientManager::slot_tcpError()
    // Slot connecté au signal error()
    // Emet le signal sig_tcpError(QString)
{
    QString tcpError = errorString();
    formatError("Tcp", tcpError);

    emit sig_tcpError(tcpError);
    emit sig_finished();
}

void TcpClientManager::slot_sqlError(QString sqlError)
    // Slot ni connecté ni appellé pour l'instant
{
    formatError("Sql", sqlError);

    emit sig_sqlError(sqlError);
    emit sig_finished();
}

void TcpClientManager::formatError(const QString& typeError, QString& error)
{
    QString currentThreadId;
    currentThreadId = QString::number(QThread::currentThreadId());

    QString errorFormatted;
    errorFormatted = typeError;
    errorFormatted += " error in (" + currentThreadId + ") : ";
    errorFormatted += error;

    error = errorFormatted;
}
