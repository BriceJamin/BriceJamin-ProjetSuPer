#ifndef TCPCLIENTMANAGER_H
#define TCPCLIENTMANAGER_H

#include <QTcpSocket>

class TcpClientManager : public QTcpSocket
{
Q_OBJECT
public:
    explicit TcpClientManager(QObject *parent = 0);

signals:

public slots:

};

#endif // TCPCLIENTMANAGER_H
