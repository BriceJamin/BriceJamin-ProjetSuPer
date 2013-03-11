#ifndef READERDETECTOR2_H
#define READERDETECTOR2_H

#include <QTcpServer>

class ReaderDetector2 : protected QTcpServer
{
Q_OBJECT

signals:
    void sig_switchedOn();
    void sig_switchedOff();

    void sig_errorOccurred(QString error);
    void sig_intruderDetected();
    void sig_readerDetected();

public slots:
    void switchOn(QString address, unsigned int port);
    void switchOff();

public:
    explicit ReaderDetector2(QObject *parent = 0);

protected:
     void incomingConnection(int socketDescriptor);
};

#endif // READERDETECTOR2_H
