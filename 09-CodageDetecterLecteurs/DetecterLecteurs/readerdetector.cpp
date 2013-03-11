#include "readerdetector2.h"
#include "tcpserverthread.h"
ReaderDetector2::ReaderDetector2(QObject *parent) :
    QTcpServer(parent)
{
}

void ReaderDetector2::switchOn(QString address, unsigned int port)
{
    if(! isListening())
    {
        tcpServer.listen(QHostAddress(address), port);

        if(isListening())
            emit sig_switchedOn();
        else
            emit sig_errorOccurred(errorString());
    }
}

void ReaderDetector2::switchOff()
{
    if(isListening())
    {
        close();
        emit sig_switchedOff();
    }
}

void ReaderDetector2::incomingConnection(int socketDescriptor)
 {
    TcpServerThread *thread = new TcpServerThread(socketDescriptor, this);

    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(sig_error(QString)), this, SIGNAL(sig_error(QString)));
    connect(thread, SIGNAL(sig_intruderDetected()), this, SIGNAL(sig_intruderDetected()));
    connect(thread, SIGNAL(sig_readerDetected()), this, SIGNAL(sig_readerDetected()));

    thread->start();
 }
