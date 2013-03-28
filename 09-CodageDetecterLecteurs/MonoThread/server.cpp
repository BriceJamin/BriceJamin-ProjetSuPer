#include "server.h"

Server::Server(QString address, quint16 port, QObject *parent) :
    QTcpServer(parent), _port(port)
{
    this->address(address);
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
    return _address.toString();
}

bool Server::address(QString address)
{
    return _address.setAddress(address);
}

unsigned int Server::port()
{
    return _port;
}

bool Server::port(unsigned int port)
{
    // TODO : Vérifier la validité du port
    _port = port;
    return true;
}
