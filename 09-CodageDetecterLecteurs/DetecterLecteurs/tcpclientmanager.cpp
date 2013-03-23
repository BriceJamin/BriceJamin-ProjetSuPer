#include <QThread>

#include "tcpclientmanager.h"

TcpClientManager::TcpClientManager(int socketDescriptor, QTcpServer *parent) :
    QTcpSocket(parent), _socketDescriptor(socketDescriptor)
{
    connect(this,
            SIGNAL(error(SocketError)),
            this,
            SLOT(slot_tcpError()));
}

void TcpClientManager::manage()
    // Slot appelé par started() lors de l'exécution d'un nouveau thread
{
    // Récupére le QTcpSocket du client à l'aide de son descripteur
    QTcpSocket tcpSocket;
    tcpSocket.setSocketDescriptor(_socketDescriptor);

    // TODO : Signaler intruderDetected si ce n'est pas un reader puis quitter
    // TODO : Signaler readerDetected si c'est un reader
}

void TcpClientManager::slot_tcpError()
    // Slot connecté au signal error()
    // Emet le signal sig_tcpError(QString)
{
    QString tcpError = errorString();
    formatError("Tcp", tcpError);

    emit sig_tcpError(tcpError);
}

void TcpClientManager::slot_sqlError(QString sqlError)
    // Slot ni connecté ni appellé pour l'instant
{
    formatError("Sql", sqlError);

    emit sig_sqlError(sqlError);
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
