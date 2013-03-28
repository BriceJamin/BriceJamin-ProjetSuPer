#include "server.h"

Server::Server(QString address, unsigned int port, QObject *parent) :
    QTcpServer(parent), _address(address), _port(port)
{
}

void Server::slot_switchOn()
{

}

void Server::slot_switchOff()
{

}
