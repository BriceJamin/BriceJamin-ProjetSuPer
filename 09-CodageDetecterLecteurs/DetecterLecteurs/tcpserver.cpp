#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{
}

void TcpServer::incomingConnection(int socketDescriptor)
 {
    /* Les clients arrivent ici. */

    /* TODO: Servir un thread à chaque client. */
 }
