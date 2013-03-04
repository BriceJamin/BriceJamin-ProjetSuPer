#include "readerdetector.h"

ReaderDetector::ReaderDetector(QObject *parent) :
    QObject(parent)
{
    connect(&tcpServer, SIGNAL(sig_clientDetected()), this, SIGNAL(sig_clientDetected()));
    connect(&tcpServer, SIGNAL(sig_intruderDetected()), this, SIGNAL(sig_intruderDetected()));
    connect(&tcpServer, SIGNAL(sig_readerDetected()), this, SIGNAL(sig_readerDetected()));
}

void ReaderDetector::switchOn(QString address, unsigned int port)
{
    if(! tcpServer.isListening())
    {
        bool noErrorOccured = tcpServer.listen(QHostAddress(address), port);

        if(noErrorOccured && tcpServer.isListening())
            emit sig_switchedOn();
        else
            emit sig_errorOccurred(tcpServer.errorString());
    }
}

void ReaderDetector::switchOff()
{
    if(tcpServer.isListening())
    {
        tcpServer.close();
        emit sig_switchedOff();
    }
}
