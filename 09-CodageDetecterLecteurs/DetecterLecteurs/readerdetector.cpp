#include "readerdetector.h"
#include "tcpclientmanager.h"
#include "thread.h"

ReaderDetector::ReaderDetector(QObject *parent) :
    QTcpServer(parent)
{
}

void ReaderDetector::switchOn(QString address, unsigned int port)
{
    if(! isListening())
    {
        listen(QHostAddress(address), port);

        if(isListening())
            emit sig_switchedOn();
        else
            emit sig_tcpServerError(errorString());
    }
}

void ReaderDetector::switchOff()
{
    if(isListening())
    {
        close();
        emit sig_switchedOff();
    }
}

void ReaderDetector::incomingConnection(int socketDescriptor)
 {
    TcpClientManager* tcpClientManager;
    tcpClientManager = new TcpClientManager(socketDescriptor, this);

    connect(tcpClientManager,
            SIGNAL(sig_intruderEjected(QString)),
            this,
            SIGNAL(sig_intruderEjected(QString)));
    connect(tcpClientManager,
            SIGNAL(sig_readerConnected(Reader*)),
            this,
            SIGNAL(sig_readerConnected(Reader*)));
    connect(tcpClientManager,
            SIGNAL(sig_readerDisconnected(Reader*)),
            this,
            SIGNAL(sig_readerDisconnected(Reader*)));
    connect(tcpClientManager,
            SIGNAL(sig_tcpError(QString)),
            this,
            SIGNAL(sig_tcpError(QString)));
    connect(tcpClientManager,
            SIGNAL(sig_sqlError(QString)),
            this,
            SIGNAL(sig_sqlError(QString)));

    // TODO : Vérifier que le TcpClientManager emit un disconnected()
    /*
    connect(this,
            SIGNAL(sig_switchedOff()),
            tcpClientManager,
            SLOT(deleteLater()));
    */

    QThread* thread;
    thread = new QThread(this);

    tcpClientManager->moveToThread(thread);

    connect(thread,
            SIGNAL(started()),
            tcpClientManager,
            SLOT(manage()));
    connect(tcpClientManager,
            SIGNAL(finished()),
            thread,
            SLOT(quit()));

    thread->start();
}
