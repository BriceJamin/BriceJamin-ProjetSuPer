#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class TcpServer : public QTcpServer
{
Q_OBJECT

signals:
    void sig_newConnection(int);

public:
    explicit TcpServer(QObject *parent = 0);

protected:
     void incomingConnection(int socketDescriptor);
};

#endif // TCPSERVER_H
