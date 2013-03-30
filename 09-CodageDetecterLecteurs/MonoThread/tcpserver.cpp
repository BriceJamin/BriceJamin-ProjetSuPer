#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{
}

void TcpServer::incomingConnection(int socketDescriptor)
{
    emit sig_newConnection(socketDescriptor);
}
