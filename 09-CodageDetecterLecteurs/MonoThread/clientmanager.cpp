#include "clientmanager.h"
#include <QDebug>
#include <QThread>

ClientManager::ClientManager(int socketDescriptor) :
    QObject(), _socketDescriptor(socketDescriptor)
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << socketDescriptor;
}

ClientManager::~ClientManager()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
}

void ClientManager::manage()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;

    if( ! setSocket())
        return;
}

void ClientManager::stop()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
    emit sig_finished();
}

bool ClientManager::setSocket()
{
    bool ok;

    ok = _tcpSocket.setSocketDescriptor(_socketDescriptor);

    if(! ok)
    {
        qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "ok:" << ok;
    }
    else
        qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "ok:" << ok;

    return ok;
}
