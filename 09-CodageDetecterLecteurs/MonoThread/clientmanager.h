#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>
#include <QTcpSocket>

class ClientManager : public QObject
{
Q_OBJECT
public:
    explicit ClientManager(int);
    ~ClientManager();

signals:

public slots:
    void manage();

private:
    int _socketDescriptor;
    QTcpSocket _tcpSocket;

};

#endif // CLIENTMANAGER_H
