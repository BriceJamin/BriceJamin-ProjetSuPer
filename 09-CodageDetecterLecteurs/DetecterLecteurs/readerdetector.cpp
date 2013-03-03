#include "readerdetector.h"

ReaderDetector::ReaderDetector(QObject *parent) :
    QObject(parent)
{
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
