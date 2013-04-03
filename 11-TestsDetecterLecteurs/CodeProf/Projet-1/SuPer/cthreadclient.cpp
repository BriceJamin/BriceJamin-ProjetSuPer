#include "cthreadclient.h"

CThreadClient::CThreadClient(QObject *parent, QTcpSocket *cl) :
    QThread(parent)
{
    client = cl;
    qDebug() << QThread::currentThreadId()
            << Q_FUNC_INFO;
} // method

//////////////////////////////////////////////////////
CThreadClient::~CThreadClient()
{
    qDebug() << QThread::currentThreadId()
            << Q_FUNC_INFO;
} // method

void CThreadClient::onFinConnexionClient()
{
    qDebug() << QThread::currentThreadId()
            << Q_FUNC_INFO
            << "Avant terminate()";
    this->terminate(); // arrêt du thread
} // method

///////////////////////////////////////////////////////
void CThreadClient::run()
 {
    qDebug() << QThread::currentThreadId()
            << Q_FUNC_INFO;
    connect(client, SIGNAL(readyRead()), this, SLOT(onLireTag()));
    connect(client, SIGNAL(destroyed()), this, SLOT(onFinConnexionClient()));
    connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
    exec();  // boucle de réception des messages du thread
} // method

////////////////////////////////////////////////////////
void CThreadClient::onLireTag()
{
    qDebug() << QThread::currentThreadId()
            << Q_FUNC_INFO;
    QString tag;
//    qDebug("Des caracteres recus");
//    qDebug(QString("%1").arg(client->bytesAvailable()).toLocal8Bit().data());
    while (client->bytesAvailable()/12 >= 1)
    {
        tag = client->read(12);
        if ( (QString::compare(tag.mid(0,1), "[")) || (QString::compare(tag.right(1), "]")) )
        {   // test validité de la trame
            while (client->read(1) != "]") {
                qDebug() << QThread::currentThreadId()
                        << Q_FUNC_INFO
                        << "Rattrapage caractere."; // synchro avec début de trame
            } // while
        } // if compare
        else
        {
            qDebug() << QThread::currentThreadId()
                    << Q_FUNC_INFO
                    << "Avant emit dataLue(tag)";
            emit(dataLue(tag));   // EMISSION SIGNAL VERS MAINWINDOW
        }
    } // while
} // method
