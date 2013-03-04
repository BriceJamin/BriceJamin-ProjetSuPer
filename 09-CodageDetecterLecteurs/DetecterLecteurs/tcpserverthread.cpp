#include "tcpserverthread.h"

TcpServerThread::TcpServerThread(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
}

void TcpServerThread::run()
{
    /* S'exécute dans un nouveau thread. */

    /* Récupère le socket du thread principal et
        en cas d'erreur émet le signal error. */
    QTcpSocket tcpSocket;
     if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
         emit sig_error(tcpSocket.error());
         return;
     }

    /* TODO : Récupérer l'adresse du client. */

    /* TODO : Demander à la BDD si c'est un lecteur. */

    /* TODO : Si c'est non, se déconnecter */

    /* TODO : Si c'est oui, lire les trames reçues
        tant que le lecteur reste connecté. */

    /* TODO : Se déconnecter. */
}
