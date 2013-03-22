#ifndef TCPCLIENTMANAGER_H
#define TCPCLIENTMANAGER_H

#include <QTcpSocket>
#include <QTcpServer>

class TcpClientManager : public QTcpSocket
{
Q_OBJECT
public:
    explicit TcpClientManager(QTcpServer *parent);

signals:

public slots:

};

#endif // TCPCLIENTMANAGER_H
