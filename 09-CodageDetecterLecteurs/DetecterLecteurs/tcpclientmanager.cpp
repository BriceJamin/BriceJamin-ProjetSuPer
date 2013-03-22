#include "tcpclientmanager.h"

TcpClientManager::TcpClientManager(QObject *parent) :
    QTcpSocket(parent)
{
}
