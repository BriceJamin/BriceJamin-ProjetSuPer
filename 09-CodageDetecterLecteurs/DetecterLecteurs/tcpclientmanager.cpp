#include "tcpclientmanager.h"

TcpClientManager::TcpClientManager(QTcpServer *parent) :
    QTcpSocket(parent)
{
}
