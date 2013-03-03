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
    void sig_on();
    void sig_error();
    void sig_addressChanged();
    void sig_portChanged();
    void sig_off();
    void sig_clientDetected();
    void sig_intruderDetected();
    void sig_readerDetected();

public slots:
    void on(QString address, unsigned int port);
    void off();

private:
    TcpServer tcpServer;
};

#endif // READERDETECTOR_H
