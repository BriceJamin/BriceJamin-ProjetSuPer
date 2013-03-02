#include "tcpserverthread.h"

TcpServerThread::TcpServerThread(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
}

void TcpServerThread::run()
{
    /* S'exécute dans le nouveau thread. */

    /* TODO : Récupérer le socket du thread principal et
        en cas d'erreur émettre le signal error. */

    /* TODO : Récupérer l'adresse du client. */

    /* TODO : Demander à la BDD si c'est un lecteur. */

    /* TODO : Si c'est non, se déconnecter */

    /* TODO : Si c'est oui, lire les trames reçues
        tant que le lecteur reste connecté. */

    /* TODO : Se déconnecter. */
}
