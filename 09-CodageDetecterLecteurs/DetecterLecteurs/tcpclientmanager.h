#ifndef TCPCLIENTMANAGER_H
#define TCPCLIENTMANAGER_H

#include <QTcpSocket>
#include <QTcpServer>

class TcpClientManager : public QTcpSocket
{
Q_OBJECT
public:
    explicit TcpClientManager(int socketDescriptor, QTcpServer *parent);

signals:

public slots:

private:
    int _socketDescriptor;
};

#endif // TCPCLIENTMANAGER_H
