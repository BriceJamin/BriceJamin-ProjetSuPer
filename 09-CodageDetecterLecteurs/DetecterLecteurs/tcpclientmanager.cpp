#include "tcpclientmanager.h"

TcpClientManager::TcpClientManager(int socketDescriptor, QTcpServer *parent) :
    QTcpSocket(parent), _socketDescriptor(socketDescriptor)
{
}

void TcpClientManager::manage()
// Slot appelé par started() lors de l'exécution d'un nouveau thread
{
}
