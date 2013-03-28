#include "server.h"


void Server::switchOn()
{
    qDebug() << Q_FUNC_INFO;

    listen(_address, _port);
}

void Server::switchOff()
{
    qDebug() << Q_FUNC_INFO;

    close();
}

bool Server::setAddress(QString address)
{
    bool ok;
    QHostAddress addressQHost;

    ok = addressQHost.setAddress(address);

    if(ok)
        _address.setAddress(address);

    qDebug() << Q_FUNC_INFO << address << "return" << ok;

    return ok;
}

bool Server::setPort(QString port)
{
    bool ok;
    ulong portULong = port.toULong(&ok);

    if(ok)
        _port = portULong;

    qDebug() << Q_FUNC_INFO << port << "return" << ok;

    return ok;
}

QString Server::address()
{
    return _address.toString();
}


quint16 Server::port()
{
    return _port;
}

Server::Server(QString address, QString port, QObject *parent) :
    QTcpServer(parent)
{
    qDebug() << Q_FUNC_INFO << address << port << parent;

    this->setAddress(address);
    this->setPort(port);
}
