#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{
    /* Le renseignement de l'adresse et du port
        se fera lors de l'appel de listen().
    */
}

void TcpServer::incomingConnection(int socketDescriptor)
 {
    /* Les clients arrivent ici. */

    /* TODO: Servir un thread à chaque client. */
 }
