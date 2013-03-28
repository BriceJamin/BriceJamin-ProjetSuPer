#include "server.h"

Server::Server(QString address, unsigned int port, QObject *parent) :
    QTcpServer(parent), _address(address), _port(port)
{
}

void Server::slot_switchOn()
{
    qDebug() << Q_FUNC_INFO;
}

void Server::slot_switchOff()
{
    qDebug() << Q_FUNC_INFO;
}

QString Server::address()
{
    return _address;
}

bool Server::address(QString address)
{
    // TODO : Verifier la validité de l'adresse
    _address = address;
    return true;
}

unsigned int Server::port()
{
    return _port;
}

bool Server::port(unsigned int port)
{
    // TODO : Verifier la validité du port
    _port = port;
    return true;
}
