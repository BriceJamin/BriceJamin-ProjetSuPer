#include "clienttcp.h"
#include <QHostAddress>

int ClientTcp::_clientsNumber = 0;

ClientTcp::ClientTcp(QObject *parent) :
    QTcpSocket(parent)
{
    _clientNumber = ++_clientsNumber;
    //_address = "127.0.0." + QString::number(_clientNumber);
    //setPeerAddress(_address);
}

ClientTcp::~ClientTcp()
{
    --_clientsNumber;
}

bool ClientTcp::setPeerAddress(const QString& address)
{
    QHostAddress host;
    if(host.setAddress(address))
    {
        QTcpSocket::setPeerAddress(host);
        _address = address;
        return true;
    }
    else
        return false;
}

QString ClientTcp::getPeerAddress()
{
   return _address;
}
