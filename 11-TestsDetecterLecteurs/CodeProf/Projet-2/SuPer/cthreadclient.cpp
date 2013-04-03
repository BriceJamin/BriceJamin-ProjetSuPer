#include "cthreadclient.h"
#include <QThread>

CThreadClient::CThreadClient(QObject *parent, QTcpSocket *cl) :
    QThread(parent)
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
    client = cl;
    qDebug("Thread running...");
} // method

//////////////////////////////////////////////////////
CThreadClient::~CThreadClient()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
    qDebug("Thread ends...");
} // method

void CThreadClient::onFinConnexionClient()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
    this->terminate(); // arrêt du thread
} // method

///////////////////////////////////////////////////////
void CThreadClient::run()
 {
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
    connect(client, SIGNAL(readyRead()), this, SLOT(onLireTag()));
    connect(client, SIGNAL(destroyed()), this, SLOT(onFinConnexionClient()));
    connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
    exec();  // boucle de réception des messages du thread
} // method

////////////////////////////////////////////////////////
void CThreadClient::onLireTag()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
    QString tag;
//    qDebug("Des caracteres recus");
//    qDebug(QString("%1").arg(client->bytesAvailable()).toLocal8Bit().data());
    while (client->bytesAvailable()/12 >= 1)
    {
        tag = client->read(12);
        if ( (QString::compare(tag.mid(0,1), "[")) || (QString::compare(tag.right(1), "]")) )
        {   // test validité de la trame
            while (client->read(1) != "]") {
                qDebug("Rattrapage caractere.");  // synchro avec début de trame
            } // while
        } // if compare
        else
            emit(dataLue(tag));   // EMISSION SIGNAL VERS MAINWINDOW
    } // while
//    else
//        qDebug("Pas assez de caractere a lire");
} // method
