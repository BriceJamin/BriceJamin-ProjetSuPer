#include "clientmanager.h"
#include <QDebug>

ClientManager::ClientManager(int socketDescriptor) :
    QObject(), _socketDescriptor(socketDescriptor)
{
    qDebug() << Q_FUNC_INFO << socketDescriptor;
}

ClientManager::~ClientManager()
{
    qDebug() << Q_FUNC_INFO;
}

void ClientManager::manage()
{
    qDebug() << Q_FUNC_INFO;
    emit sig_finished();
}
