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
    void sig_finished();

public slots:
    void manage();
    void stop();

private:
    int _socketDescriptor;
    QTcpSocket _tcpSocket;

};

#endif // CLIENTMANAGER_H
