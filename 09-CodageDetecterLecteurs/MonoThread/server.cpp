#include "server.h"

Server::SwitchOnState Server::switchOn()
{
    SwitchOnState state = Success;

    if(! isListening())
    {
        bool ok = listen(_address, _port);

        if(ok)
        {
            qDebug() << Q_FUNC_INFO << "-> sig_switchedOn";

            emit sig_switchedOn();
        }
        else
        {
            QAbstractSocket::SocketError socketError = serverError();

            switch(socketError)
            {
            case QAbstractSocket::SocketAddressNotAvailableError:
                state = this->AddressNotAvailableError;
                break;

            case QAbstractSocket::SocketAccessError:
                state = this->PortProtectedError;
                break;

            case QAbstractSocket::AddressInUseError:
                state = this->PortAlreadyInUseError;
                break;

            default:
                state = this->UnknownError;
            }

            qDebug() << Q_FUNC_INFO << "erreur listen, return " << state;
        }
    }
    else
        qDebug() << Q_FUNC_INFO << "ignore (deja en ecoute), return" << state;

    return state;
}

void Server::switchOff()
{
    if(isListening())
    {
        qDebug() << Q_FUNC_INFO << "close -> sig_switchedOff";

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
            qDebug() << Q_FUNC_INFO << address << "-> sig_addressChanged, return" << ok;

            _address.setAddress(address);
            emit sig_addressChanged(address);
        }
        else
            qDebug() << Q_FUNC_INFO << address << "mauvais format, return" << ok;
    }
    else
        qDebug() << Q_FUNC_INFO << address << "ignore (deja en ecoute), return" << ok;

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
            qDebug() << Q_FUNC_INFO << port << "-> sig_portChanged, return" << ok;

            _port = portQuint16;
            emit sig_portChanged(portQuint16);
        }
        else
            qDebug() << Q_FUNC_INFO << port << "mauvais format, return" << ok;
    }
    else
         qDebug() << Q_FUNC_INFO << port << "ignore (deja en ecoute), return" << ok;

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
