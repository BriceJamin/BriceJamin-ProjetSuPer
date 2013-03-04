#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{
}

void TcpServer::incomingConnection(int socketDescriptor)
 {
    /* Les clients arrivent ici. */
    emit sig_clientDetected();

    /* TODO: Servir un thread à chaque client. */
 }
