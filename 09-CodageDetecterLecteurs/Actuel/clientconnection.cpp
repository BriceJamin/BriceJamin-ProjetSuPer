#include "clientconnection.h"
#include "reader.h"
#include <QThread>
#include <QMetaType>

ClientConnection::ClientConnection(int socketDescriptor) :
    QObject(), _socketDescriptor(socketDescriptor)
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << socketDescriptor;
    _tcpSocket.setParent(this);

    this->connect(&_tcpSocket, SIGNAL(connected()), SIGNAL(sig_connected()));
    this->connect(&_tcpSocket, SIGNAL(disconnected()), SIGNAL(sig_disconnected()));
}

ClientConnection::~ClientConnection()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
}
void ClientConnection::open()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "avant setSocketDescriptor";

    bool ok = _tcpSocket.setSocketDescriptor(_socketDescriptor);

    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "setSocketDescriptor:" << ok;

    if(_tcpSocket.isValid())
        filter();
    else
        delete this;
}

void ClientConnection::close()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
    _tcpSocket.close();
    emit sig_closed();
}

void ClientConnection::filter()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
    bool isAReader = false;

    QString address = _tcpSocket.peerAddress().toString();
    if(address == "127.0.0.1")
        isAReader = true;

    if(isAReader)
    {
        Reader reader;
        qRegisterMetaType<Reader>("Reader");
        emit sig_isAReader(reader);
        this->connect(&_tcpSocket, SIGNAL(readyRead()), SLOT(readyRead()));
    }
    else
        emit sig_isNotAReader(address);
}

void ClientConnection::readyRead()
{
    qint64 nbBytesAvailable = _tcpSocket.bytesAvailable();
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "bytesAvailable:" << nbBytesAvailable;

    if(nbBytesAvailable > 0)
    {
        QString data = _tcpSocket.readAll();
        emit sig_dataRead(data);
    }
}

