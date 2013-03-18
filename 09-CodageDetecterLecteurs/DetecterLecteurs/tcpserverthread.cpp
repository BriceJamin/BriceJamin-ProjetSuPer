#include "tcpserverthread.h"
#include <QHostAddress>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "reader.h"

TcpServerThread::TcpServerThread(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
}

TcpServerThread::~TcpServerThread()
{
    /* Stoppe proprement l'exécution du Thread */
    quit();
    wait();
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
    QString nameDatabaseConnexion = QString::number(QThread::currentThreadId());
    unsigned int number;
    unsigned int placeId;
    QString address;
    bool isConnected;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", nameDatabaseConnexion);
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
        number = query.value(0).toInt();
        placeId = query.value(1).toInt();
        address = query.value(2).toString();
        isConnected = query.value(3).toBool();
        db.close();
    }

    QSqlDatabase::removeDatabase(nameDatabaseConnexion);

    /* TODO : Faire un constructeur par défaut pour ReaderData */
    /* TODO : L'utiliser pour éviter de trimbaler les attributs en dehors */
    ReaderData readerData(number, placeId, address, isConnected);
    Reader reader(readerData);

    qDebug() << "TcpServerThread(" << QThread::currentThreadId() << ") :" << endl
        << "  Le client est le lecteur de numero " << reader.data().number() << "," << endl
        << "  de lieu numero " << reader.data().placeId() << "," << endl
        << "  d'ip " << reader.data().address() << "," << endl
        << "  et de estConnecte " << reader.data().isConnected() << ".";

    /* Signale la détection d'un lecteur */
    emit sig_readerDetected(&reader);

    /* TODO : Signaler la déconnexion d'un lecteur
    connect(&tcpSocket, SIGNAL(disconnected()), this, ??? );*/

    /* TODO : Tuer le thread lorsqu'un lecteur se déconnecte.*/

    /* TODO : Lire les trames reçues tant que le lecteur reste connecté. */

    exec();
}
