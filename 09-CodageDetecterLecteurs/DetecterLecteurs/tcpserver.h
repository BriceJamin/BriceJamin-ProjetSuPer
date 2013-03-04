#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class TcpServer : public QTcpServer
{
Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);

signals:
    void sig_clientDetected();
    void sig_intruderDetected();
    void sig_readerDetected();

public slots:

protected:
     void incomingConnection(int socketDescriptor);

};

#endif // TCPSERVER_H
