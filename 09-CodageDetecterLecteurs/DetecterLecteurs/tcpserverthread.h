#ifndef TCPSERVERTHREAD_H
#define TCPSERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "reader.h"

class TcpServerThread : public QThread
{
Q_OBJECT
public:
    explicit TcpServerThread(int socketDescriptor, QObject *parent);

    void run();

signals:
    void sig_errorOccurred(QString);
    void sig_intruderDetected(QString clientAddress);
    void sig_readerDetected(const Reader& reader);

public slots:

private:
    int socketDescriptor;
};

#endif // TCPSERVERTHREAD_H
