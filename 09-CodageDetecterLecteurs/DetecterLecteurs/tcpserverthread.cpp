#include "tcpserverthread.h"
#include <QHostAddress>
#include <QSqlDatabase>

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

    /* Récupère l'adresse du client. */
    QString peerAddress = tcpSocket.peerAddress().toString();

    /* Demande à la BDD si c'est un lecteur. */
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("bdd_super");
    db.setUserName("user_super");
    db.setPassword("mdp_super");
    if (!db.open())
    {
        qDebug() << "Impossible d'etablir une connexion avec la Bdd.";

        /* TODO : Sortir du thread */
    }
    else
        qDebug() << "Connexion a la bdd reussie.";

    QSqlQuery query(db);
    query.exec("SELECT  num_lecteur, num_lieu, ip, estConnecte FROM lecteur WHERE ip like \"" + peerAddress + "\"");
    if(!query.isActive())
    {
        qDebug() << "Requete (Ce lecteur d'ip X existe t'il ?) erronnée.";

        /* TODO : Tuer le thread */
    }
    else if(query.size() == 0)
    {
        qDebug() << "Le client n'est pas un lecteur.";

        /* TODO : Emettre un signal "intrus detecte" */
        /* TODO : Déconnecter le client */
        /* TODO : Tuer le thread */
    }
    else
    {
        query.next();
        qDebug() << "Le client est le lecteur de numero " + QString::number(query.value(0).toInt()) + ",";
        qDebug() << "de lieu numero " + QString::number(query.value(1).toInt()) + ",";
        qDebug() << "d'ip " + query.value(2).toString() + ",";
        qDebug() << "et de estConnecte " + QString::number(query.value(3).toInt()) + ".";

        /* TODO : Créer une classe Lecteur */
        /* TODO : Instancier un objet de la classe Lecteur */
        /* TODO : Emettre un signal "lecteur connecté" avec ce lecteur en paramètre */

        /* TODO : Lire les trames reçues tant que le lecteur reste connecté. */
        /* TODO : Tuer le thread */
    }
}
