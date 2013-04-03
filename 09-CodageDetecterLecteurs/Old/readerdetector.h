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

    void sig_intruderEjected(QString address);
    void sig_readerConnected(Reader* reader);
    void sig_readerDisconnected(Reader* reader);

    void sig_tcpClientError(QString);
    void sig_tcpServerError(QString);
    void sig_sqlError(QString);

public slots:
    void switchOn(QString address, unsigned int port);
    void switchOff();

public:
    explicit ReaderDetector(QObject *parent = 0);

protected:
     void incomingConnection(int socketDescriptor);
};

#endif // READERDETECTOR_H
