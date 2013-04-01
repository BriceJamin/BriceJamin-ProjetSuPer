#include "clientmanager.h"

ClientManager::ClientManager(int socketDescriptor) :
    QObject(), _socketDescriptor(socketDescriptor)
{
}
