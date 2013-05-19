#include "clientconnection.h"
#include "reader.h"
#include "bddConfig.h"
#include <QThread>
#include <QMetaType>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

ClientConnection::ClientConnection(int socketDescriptor) :
    QObject(), _socketDescriptor(socketDescriptor), _opened(false)
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << socketDescriptor;
    _tcpSocket.setParent(this);

    this->connect(&_tcpSocket, SIGNAL(disconnected()), SIGNAL(sig_disconnected()));
    // TODO this->connect(&_tcpSocket, SIGNAL(disconnected()), SLOT(deleteLater()));
}

ClientConnection::~ClientConnection()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
    _tcpSocket.close();
}

void ClientConnection::open()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;

    if(! _opened)
    {
        _tcpSocket.setSocketDescriptor(_socketDescriptor);

        if(_tcpSocket.isValid())
        {
            _opened = true;

            qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "_tcpSocket.isValid()," << _opened;

             // Activation de l'option KeepAlive
            _tcpSocket.setSocketOption(QAbstractSocket::KeepAliveOption, 1);

            filter();
        }
        else
        {
            emit sig_error("socket invalid"); // TODO : Utiliser un enum ?
            deleteLater();
        }
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
        db.setConnectOptions("MYSQL_OPT_RECONNECT=5");
        db.setHostName(BDD_HOST_NAME);
        // TODO : Envoyer un nom invalide à setDatabaseName pour tester le comportement du code
        db.setDatabaseName(BDD_DATABASE_NAME);
        db.setUserName(BDD_USER_NAME);
        db.setPassword(BDD_PASSWORD);
        if (!db.open())
        {
            qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "Error : QSqlDatabase::open() fail :" << db.lastError();
            emit sig_error("open database error");
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
                qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "Error : QSqlQuery::exec() [reader ip" << clientAddress << "exists ?] fail.";
                emit sig_error("sql error : [Select reader infos]");
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

                        emit sig_error("sql error : [Update reader.isConnected]");
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
