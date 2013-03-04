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
    void sig_error(QTcpSocket::SocketError socketError);
    void sig_intruderDetected();
    void sig_readerDetected();

public slots:

private:
    int socketDescriptor;
};

#endif // TCPSERVERTHREAD_H
