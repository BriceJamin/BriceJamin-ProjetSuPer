#include "server.h"

void Server::switchOn()
{
    if(! isListening())
    {
        qDebug() << Q_FUNC_INFO << "listen et sig_switchedOn";

        if( listen(_address, _port) )
            emit sig_switchedOn();
    }
    else
        qDebug() << Q_FUNC_INFO;
}

void Server::switchOff()
{
    if(isListening())
    {
        qDebug() << Q_FUNC_INFO << " -> close et sig_switchedOff";

        close();
        emit sig_switchedOff();
    }
    else
        qDebug() << Q_FUNC_INFO;
}

bool Server::setAddress(QString address)
{
    bool ok = false;

    if(! isListening())
    {
        QHostAddress addressQHost;

        ok = addressQHost.setAddress(address);

        if(ok)
        {
            qDebug() << Q_FUNC_INFO << address << "sig_addressChanged()";

            _address.setAddress(address);
            emit sig_addressChanged(address);
        }
    }

    qDebug() << Q_FUNC_INFO << address << "return" << ok;

    return ok;
}

bool Server::setPort(QString port)
{
    bool ok = false;

    if(! isListening())
    {
        quint16 portQuint16 = port.toULong(&ok); // quint16 <=> ulong

        if(ok)
        {
            qDebug() << Q_FUNC_INFO << port << "sig_portChanged()";

            _port = portQuint16;
            emit sig_portChanged(portQuint16);
        }
    }

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

Server::~Server()
{
    qDebug() << Q_FUNC_INFO;

    close();
}
