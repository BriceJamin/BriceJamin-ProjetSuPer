#ifndef READERDETECTOR_H
#define READERDETECTOR_H

#include <QTcpServer>
#include "reader.h"

class ReaderDetector : public QTcpServer
{
Q_OBJECT

signals:
    void sig_switchedOn();
    void sig_switchedOff();

    void sig_errorOccurred(QString error);
    void sig_intruderEjected(QString address);
    void sig_readerConnected(Reader* reader);
    void sig_readerDisconnected(Reader* reader);

public slots:
    void switchOn(QString address, unsigned int port);
    void switchOff();

public:
    explicit ReaderDetector(QObject *parent = 0);

protected:
     void incomingConnection(int socketDescriptor);
};

#endif // READERDETECTOR_H
