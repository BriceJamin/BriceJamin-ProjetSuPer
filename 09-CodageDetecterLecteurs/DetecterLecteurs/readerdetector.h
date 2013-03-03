#ifndef READERDETECTOR_H
#define READERDETECTOR_H

#include <QObject>
#include "tcpserver.h"

class ReaderDetector : public QObject
{
Q_OBJECT
public:
    explicit ReaderDetector(QObject *parent = 0);

signals:
    void sig_switchedOn();
    void sig_errorOccurred(QString error);
    void sig_switchedOff();
    void sig_clientDetected();
    void sig_intruderDetected();
    void sig_readerDetected();

public slots:
    void switchOn(QString address, unsigned int port);
    void switchOff();

private:
    TcpServer tcpServer;
};

#endif // READERDETECTOR_H
