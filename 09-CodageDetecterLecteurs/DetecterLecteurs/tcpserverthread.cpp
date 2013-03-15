#include "tcpserverthread.h"
#include <QHostAddress>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "reader.h"

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
         emit sig_errorOccurred(tcpSocket.errorString());
         /* Termine l'exécution du thread */
         return;
     }

    /* Récupère l'adresse du client. */
    QString clientAddress = tcpSocket.peerAddress().toString();
    qDebug() << "Connexion du client d'origine' " << clientAddress
            << ", port " << tcpSocket.peerPort()
            << " vers " << tcpSocket.localAddress()
            << ", port " << tcpSocket.localPort();

    /* Demande à la BDD si c'est un lecteur. */
    /* TODO : Créer une classe servant d'interface à la BDD */
    /* TODO : Se renseigner sur l'accès à une BDD via des threads */
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", QString::number(QThread::currentThreadId()));
    db.setHostName("localhost");
    db.setDatabaseName("bdd_super");
    db.setUserName("user_super");
    db.setPassword("mdp_super");
    if (!db.open())
    {
        qFatal("Impossible d'etablir une connexion avec la Bdd.");
        /* Termine l'exécution du thread */
        return;
    }

    qDebug() << "TcpServerThread : Connexion a la bdd reussie.";

    QSqlQuery query(db);
    query.exec("SELECT  num_lecteur, num_lieu, ip, estConnecte FROM lecteur WHERE ip like \"" + clientAddress + "\"");
    if(!query.isActive())
    {
        qFatal("TcpServerThread : Requete sql (Ce lecteur d'ip X existe t'il ?) erronnée.");

        /*  Termine l'exécution du thread */
        return;
    }

    if(query.size() == 0)
    {
        qDebug() << "TcpServerThread : Le client " + clientAddress + " n'est pas un lecteur.";

        /* Signale la détection d'un intrus */
        emit sig_intruderDetected(clientAddress);

        /* TODO : Déconnecter le client proprement */

        /* Termine l'exécution du thread */
        return;
    }

    query.next();
    unsigned int number = query.value(0).toInt();
    unsigned int placeId = query.value(1).toInt();
    QString address = query.value(2).toString();
    bool isConnected = query.value(3).toBool();

    ReaderData readerData(number, placeId, address, isConnected);
    Reader reader(readerData);

    qDebug() << "TcpServerThread(" << QThread::currentThreadId() << ") :" << endl
        << "  Le client est le lecteur de numero " << reader.data().number() << "," << endl
        << "  de lieu numero " << reader.data().placeId() << "," << endl
        << "  d'ip " << reader.data().address() << "," << endl
        << "  et de estConnecte " << reader.data().isConnected() << ".";

    /* Signale la détection d'un lecteur */
    emit sig_readerDetected(&reader);

    /* TODO : Lire les trames reçues tant que le lecteur reste connecté. */
    /* TODO : Tuer le thread */

    /* TODO (?) : Terminer l'exécution du thread lors d'une déconnexion ?
    connect(&tcpSocket, SIGNAL(disconnected()), this, ;*/

    exec();
}
