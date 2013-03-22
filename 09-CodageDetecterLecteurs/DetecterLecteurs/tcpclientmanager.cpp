#include "tcpclientmanager.h"

TcpClientManager::TcpClientManager(int socketDescriptor, QTcpServer *parent) :
    QTcpSocket(parent), _socketDescriptor(socketDescriptor)
{
}
