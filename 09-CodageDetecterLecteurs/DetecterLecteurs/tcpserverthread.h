#ifndef TCPSERVERTHREAD_H
#define TCPSERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>

class TcpServerThread : public QThread
{
Q_OBJECT
public:
    explicit TcpServerThread(int socketDescriptor, QObject *parent);

    void run();

signals:
    void error(QTcpSocket::SocketError socketError);

public slots:

private:
    int socketDescriptor;
};

#endif // TCPSERVERTHREAD_H
