#include "clientconnection.h"
#include "reader.h"
#include <QThread>
#include <QMetaType>
#include <QSqlDatabase>
#include <QSqlQuery>

ClientConnection::ClientConnection(int socketDescriptor) :
    QObject(), _socketDescriptor(socketDescriptor)
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << socketDescriptor;
    _tcpSocket.setParent(this);

    this->connect(&_tcpSocket, SIGNAL(disconnected()), SIGNAL(sig_disconnected()));
}

ClientConnection::~ClientConnection()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
}

void ClientConnection::open()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "avant setSocketDescriptor";

    _tcpSocket.setSocketDescriptor(_socketDescriptor);

    if(_tcpSocket.isValid())
    {
        qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "_tcpSocket.isValid()";

         // Activation de l'option KeepAlive
        _tcpSocket.setSocketOption(QAbstractSocket::KeepAliveOption, 1);

        filter();
    }
    else
    {
        emit sig_error("socket invalid"); // TODO : Utiliser un enum
        deleteLater();
    }
}

void ClientConnection::close()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
    _tcpSocket.close();
    emit sig_closed(); // TODO : Supprimer ?
}

void ClientConnection::filter()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;

    // Récupère l'adresse du client.
    QString clientAddress = _tcpSocket.peerAddress().toString();

    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "clientAddress:" << clientAddress;

    // Demande à la BDD si c'est un lecteur.
    QString nameDatabaseConnexion = QString::number(QThread::currentThreadId());
    Reader reader;

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", nameDatabaseConnexion);
        // TODO : Stoquer ces constantes dans des variables initialisées à un endroit plus visible (.h ?)
        db.setHostName("localhost");
        // TODO : Envoyer un nom invalide à setDatabaseName pour tester le comportement du code
        db.setDatabaseName("bdd_super");
        db.setUserName("user_super");
        db.setPassword("mdp_super");
        if (!db.open())
        {
            qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "Error : QSqlDatabase::open() fail.";
            // TODO : Emettre signal d'erreur
            // TODO : Stopper proprement
            _tcpSocket.close();
        }
        else
        {
            qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "QSqlDatabase::open() : Success.";

            QSqlQuery query(db);
            // TODO : Glisser une erreur de requete pour tester le comportement du code
            query.exec("SELECT  num_lecteur, num_lieu, ip, estConnecte FROM lecteur WHERE ip like \"" + clientAddress + "\"");
            if(!query.isActive())
            {
                qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "Error : QSqlQuery::exec() [lecteur d'ip" << clientAddress << "existe ?] fail.";
                // TODO : Emettre signal d'erreur
                // TODO : Stopper proprement
                _tcpSocket.close();
            }
            else
            {
                qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "QSqlQuery::exec() [lecteur d'ip X existe ?] ok";

                if(query.size() == 0)
                {
                    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "query.size() == 0 -> isNotAReader";
                    // Signale la détection d'un intrus
                    emit sig_isNotAReader(clientAddress);
                }
                else
                {
                    query.next();
                    reader.number(query.value(0).toInt());
                    reader.placeId(query.value(1).toInt());
                    reader.address(query.value(2).toString());
                    reader.isConnected(true);
                    query.finish();

                    // Update BDD (lecteur connecté)
                    // TODO : Glisser une erreur de requete pour tester le comportement du code
                    query.exec("UPDATE lecteur SET estConnecte=" + QString::number(reader.isConnected()) + " WHERE ip=\"" + reader.address() + "\";");
                    if(!query.isActive())
                    {
                        qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "QSqlQuery::exec() [Update lecteur.estConnecte] ERROR";

                        // TODO : Emettre signal d'erreur
                        // TODO : Stopper proprement
                    }
                    else
                    {
                        query.finish();

                        qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "QSqlQuery::exec() [Update lecteur.estConnecte] ok -> sig_isAReader(reader)";
                        qRegisterMetaType<Reader>("Reader");
                        emit sig_isAReader(reader);

                        this->connect(&_tcpSocket, SIGNAL(readyRead()), SLOT(readyRead()));
                    }
                }
            }
            db.close();
        }
    }

    QSqlDatabase::removeDatabase(nameDatabaseConnexion);
}

void ClientConnection::readyRead()
{
    qint64 nbBytesAvailable = _tcpSocket.bytesAvailable();
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "bytesAvailable:" << nbBytesAvailable;

    if(nbBytesAvailable > 0)
    {
        QString data = _tcpSocket.readAll();
        emit sig_dataRead(data);
    }
}
