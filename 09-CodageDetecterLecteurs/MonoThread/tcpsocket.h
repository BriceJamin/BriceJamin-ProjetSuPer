#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>

class TcpSocket : public QTcpSocket
{
Q_OBJECT
public:
    explicit TcpSocket(QObject *parent = 0);
};

#endif // TCPSOCKET_H
