#include "readerdetector.h"
#include "tcpserverthread.h"
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
    TcpServerThread *thread = new TcpServerThread(socketDescriptor, this);

    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(sig_errorOccurred(QString)), this, SIGNAL(sig_errorOccurred(QString)));
    connect(thread, SIGNAL(sig_intruderEjected(QString)), this, SIGNAL(sig_intruderEjected(QString)));
    connect(thread, SIGNAL(sig_readerConnected(Reader*)), this, SIGNAL(sig_readerConnected(Reader*)));
    connect(thread, SIGNAL(sig_readerDisconnected(Reader*)), this, SIGNAL(sig_readerDisconnected(Reader*)));

    thread->start();
 }
