#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{
    qDebug() << Q_FUNC_INFO << parent;
}

TcpServer::~TcpServer()
{
    qDebug() << Q_FUNC_INFO << "close()";

    close();
}

void TcpServer::incomingConnection(int socketDescriptor)
{
    qDebug() << Q_FUNC_INFO << "-> sig_newConnection" << socketDescriptor;

    emit sig_newConnection(socketDescriptor);
}
