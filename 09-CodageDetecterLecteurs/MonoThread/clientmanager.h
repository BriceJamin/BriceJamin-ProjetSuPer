#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>

class ClientManager : public QObject
{
Q_OBJECT
public:
    explicit ClientManager(int);

signals:

public slots:

private:
    int socketDescriptor;

};

#endif // CLIENTMANAGER_H
