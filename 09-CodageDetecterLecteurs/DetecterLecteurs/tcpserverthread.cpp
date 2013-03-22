#include "tcpserverthread.h"
#include <QHostAddress>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "reader.h"

// TODO : Quitter proprement lors d'une erreur sans redondance de code
// TODO : Créer une classe servant d'interface à la BDD

TcpServerThread::TcpServerThread(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
}

TcpServerThread::~TcpServerThread()
{
    // Stoppe proprement l'exécution du Thread
    quit();
    wait();
}

void TcpServerThread::run()
{
    // S'exécute dans un nouveau thread.

    qDebug() << "TcpServerThread(" << QThread::currentThreadId() << ") :";

    /*
       Récupère le socket du thread principal et
       en cas d'erreur émet le signal error.
    */
    QTcpSocket tcpSocket;
     if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
         emit sig_errorOccurred(tcpSocket.errorString());
         /* Termine l'exécution du thread */
         return;
     }

    // Récupère l'adresse du client.
    QString clientAddress = tcpSocket.peerAddress().toString();

    qDebug() << "Connexion du client d'origine " << clientAddress
            << "port " << tcpSocket.peerPort()
            << ", vers " << tcpSocket.localAddress().toString()
            << "port " << tcpSocket.localPort();

    // Demande à la BDD si c'est un lecteur.
    QString nameDatabaseConnexion = QString::number(QThread::currentThreadId());

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", nameDatabaseConnexion);
        db.setHostName("localhost");
        db.setDatabaseName("bdd_super");
        db.setUserName("user_super");
        db.setPassword("mdp_super");
        if (!db.open())
        {
            qFatal("TcpServerThread::run() : Impossible d'etablir une connexion avec la Bdd.");
            /* Termine l'exécution du thread */
            return;
        }

        qDebug() << "TcpServerThread::run() : Connexion a la bdd reussie.";

        QSqlQuery query(db);
        query.exec("SELECT  num_lecteur, num_lieu, ip, estConnecte FROM lecteur WHERE ip like \"" + clientAddress + "\"");
        if(!query.isActive())
        {
            qFatal("TcpServerThread::run() : Requete sql (Ce lecteur d'ip X existe t'il ?) erronnee.");

            /*  Termine l'exécution du thread */
            return;
        }

        if(query.size() == 0)
        {
            qDebug() << "TcpServerThread::run() : Le client " + clientAddress + " n'est pas un lecteur.";

            /* Signale la détection d'un intrus */
            emit sig_intruderEjected(clientAddress);

            /* TODO : Déconnecter le client proprement */

            /* Termine l'exécution du thread */
            return;
        }

        query.next();
        reader.number(query.value(0).toInt());
        reader.placeId(query.value(1).toInt());
        reader.address(query.value(2).toString());
        reader.isConnected(true);
        query.finish();

        // Mise à jour de la BDD (le lecteur est désormais connecté)
        query.exec("UPDATE lecteur SET estConnecte=" + QString::number(reader.isConnected()) + " WHERE ip=\"" + reader.address() + "\";");
        if(!query.isActive())
        {
            qFatal("TcpServerThread::run() : Requete sql (Mise à jour de estConnecte du lecteur) erronnee.");

            /*  Termine l'exécution du thread */
            return;
        }
        query.finish();
        db.close();
    }

    QSqlDatabase::removeDatabase(nameDatabaseConnexion);

    qDebug() << "Le client est le lecteur num(" << reader.number() << "),"
        << "placeId(" << reader.placeId() << "),"
        << "address(" << reader.address() << "),"
        << "isConnected(" << reader.isConnected() << ").";

    /* Signale la détection d'un lecteur */
    emit sig_readerConnected(&reader);

    /* Signalera la déconnexion du lecteur */
    connect(&tcpSocket, SIGNAL(disconnected()), this, SLOT(slot_socketDisconnected()));

    /* TODO : Tuer le thread lorsqu'un lecteur se déconnecte.*/

    /* TODO : Lire les trames reçues tant que le lecteur reste connecté. */

    exec();
}

void TcpServerThread::slot_socketDisconnected()
{
    reader.isConnected(false);
    // Mise à jour de la BDD (le lecteur est désormais déconnecté)
    QString nameDatabaseConnexion = QString::number(QThread::currentThreadId());
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", nameDatabaseConnexion);
        db.setHostName("localhost");
        db.setDatabaseName("bdd_super");
        db.setUserName("user_super");
        db.setPassword("mdp_super");
        if (!db.open())
        {
            qFatal("TcpServerThread::slot_socketDisconnected() : Impossible d'etablir une connexion avec la Bdd.");
            /* Termine l'exécution du thread */
            return;
        }

        QSqlQuery query(db);
        query.exec("UPDATE lecteur SET estConnecte=" + QString::number(reader.isConnected()) + " WHERE ip=\"" + reader.address() + "\";");
        if(!query.isActive())
        {
            qFatal("TcpServerThread::slot_socketDisconnected() : Requete sql () erronnee.");

            /*  Termine l'exécution du thread */
            return;
        }
    }

    QSqlDatabase::removeDatabase(nameDatabaseConnexion);

    emit sig_readerDisconnected(&reader);
}
