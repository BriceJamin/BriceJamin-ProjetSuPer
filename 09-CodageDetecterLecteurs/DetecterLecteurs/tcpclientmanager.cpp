#include "tcpclientmanager.h"

TcpClientManager::TcpClientManager(int socketDescriptor, QTcpServer *parent) :
    QTcpSocket(parent), _socketDescriptor(socketDescriptor)
{
}

void TcpClientManager::manage()
// Slot appelé par started() lors de l'exécution d'un nouveau thread
{
    // TODO : Récupérer le QTcpSocket du client à l'aide de son descripteur
    // TODO : Signaler intruderDetected si ce n'est pas un reader puis quitter
    // TODO : Signaler readerDetected si c'est un reader
}
