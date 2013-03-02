#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{
    /* TODO: Renseigner l'adresse et le port */
}

void TcpServer::incomingConnection(int socketDescriptor)
 {
    /* Les clients arrivent ici. */

    /* TODO: Servir un thread à chaque client. */
 }
