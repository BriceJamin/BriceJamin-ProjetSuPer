#include "server.h"

Server::SwitchOnState Server::switchOn()
{
    SwitchOnState state = Success;

    if(! _server.isListening())
    {
        bool ok = _server.listen(_address, _port);

        if(ok)
        {
            qDebug() << Q_FUNC_INFO << "-> sig_switchedOn";

            _setAddress(_server.serverAddress().toString());
            _setPort(QString::number(_server.serverPort()));

            emit sig_switchedOn();
        }
        else
        {
            QAbstractSocket::SocketError socketError = _server.serverError();

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
    if(_server.isListening())
    {
        qDebug() << Q_FUNC_INFO << "close -> sig_switchedOff";

        _server.close();
        emit sig_switchedOff();
    }
    else
        qDebug() << Q_FUNC_INFO;
}

bool Server::setAddress(QString address)
{
    bool ok = false;

    if(! _server.isListening())
        ok = _setAddress(address);
    else
        qDebug() << Q_FUNC_INFO << address << "ignore (deja en ecoute), return" << ok;

    return ok;
}

bool Server::setPort(QString port)
{
    bool ok = false;

    if(! _server.isListening())
    {
        ok = _setPort(port);
    }
    else
         qDebug() << Q_FUNC_INFO << port << "ignore (deja en ecoute), return" << ok;

    return ok;
}

Server::Server(QString address, QString port, QObject *parent) :
    QObject(parent)
{
    qDebug() << Q_FUNC_INFO << address << port << parent;

    _setAddress(address);
    _setPort(port);
}

Server::~Server()
{
    qDebug() << Q_FUNC_INFO;
}

QString Server::address()
{
    return _address.toString();
}

quint16 Server::port()
{
    return _port;
}

void Server::incomingConnection(int socketDescriptor)
{
    qDebug() << Q_FUNC_INFO << socketDescriptor;
}

bool Server::_setAddress(QString address)
{
    bool ok;
    QHostAddress addressQHost;

    ok = addressQHost.setAddress(address);

    if(ok && addressQHost != _address)
    {
        qDebug() << Q_FUNC_INFO << address << "-> sig_addressChanged, return" << ok;

        _address.setAddress(address);
        emit sig_addressChanged(address);
    }
    else
        qDebug() << Q_FUNC_INFO << address << "ignore (mauvais format ou meme valeur), return" << ok;

    return ok;
}

bool Server::_setPort(QString port)
{
    bool ok;
    quint16 portQuint16 = port.toULong(&ok); // quint16 <=> ulong

    if(ok && portQuint16 != _port)
    {
        qDebug() << Q_FUNC_INFO << port << "-> sig_portChanged, return" << ok;

        _port = portQuint16;
        emit sig_portChanged(portQuint16);
    }
    else
        qDebug() << Q_FUNC_INFO << port << "ignore (mauvais format ou meme valeur), return" << ok;

    return ok;
}

QDebug operator<<(QDebug debug, const Server::SwitchOnState& state)
{
    QString stateString;

    switch(state)
    {
    case Server::Success:
        stateString = "Success";
        break;
    case Server::AddressNotAvailableError:
        stateString = "AddressNotAvailableError";
        break;
    case Server::PortProtectedError:
        stateString = "PortProtectedError";
        break;
    case Server::PortAlreadyInUseError:
        stateString = "PortAlreadyInUseError";
        break;
    case Server::UnknownError:
        stateString = "UnknownError";
        break;
    }

    debug << stateString;

    return debug.nospace();
}
