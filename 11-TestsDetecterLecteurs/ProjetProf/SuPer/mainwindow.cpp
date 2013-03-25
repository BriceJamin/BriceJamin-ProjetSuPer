#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) ,
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    nbT = 0;   // nbre de trame
    nbB = 0;   // nbre de badges
    nbLect=0; // aucun lecteur connecté

    // pour le réseau
    serv = new QTcpServer(this);
    serv->listen(QHostAddress::Any, 2222);
    connect(serv, SIGNAL(newConnection()), this, SLOT(onGererThread()));
    qDebug() << QThread::currentThreadId()
            << Q_FUNC_INFO;
} // method

MainWindow::~MainWindow()
{
    qDebug() << QThread::currentThreadId()
            << Q_FUNC_INFO;

    delete serv;
    
    T_Thread *th;
    while (!lecteurs.isEmpty()) {
        th = lecteurs.takeFirst();
        delete th->thcl;
        delete th;
    } // while
    lecteurs.clear();
    delete aff;
    delete ui;
} // method

///////////////////////////////////////////////////////////
void MainWindow::onEffacerUnThread() {
    qDebug() << QThread::currentThreadId()
            << Q_FUNC_INFO;
    T_Thread *th;
    int nb;

    nb = lecteurs.size();
    for (int i=0 ; i<nb ; i++) {
        th = lecteurs.at(i);
        if (th->thcl->isFinished()) {
            qDebug() << QThread::currentThreadId()
                    << Q_FUNC_INFO << "Pb de communication avec le lecteur :"
                    << QString("%1").arg(th->noLect);
            delete th->thcl;
            delete th;
            lecteurs.removeAt(i);
            nbLect--;
            break;
        } // if finish
    } // for
} // method

///////////////////////////////////////////////////////////
// return true si trame au bon format
bool MainWindow::traitement(QString &trame) {
    qDebug() << QThread::currentThreadId()
            << Q_FUNC_INFO;
    QString noBadge, sens, lect, mouv;

    nbT++; // compteur de trames

    // séparation des parties de la trame
    noBadge = trame.mid(3,3);
    if (noBadge == "000")
    {
        qDebug() << QThread::currentThreadId()
                << Q_FUNC_INFO
                << "Mauvais badge no=000";
     return false;
    }
    sens = trame.mid(1,2);
    mouv = trame.mid(6,3);
    lect = trame.mid(9,2);

    // affichage ihm
    qDebug() << QThread::currentThreadId()
             << Q_FUNC_INFO
             << "S:" << sens
             << " B:" << noBadge
             << " M:" << mouv
             << " L:" << lect
             << trame;

    return true;
}

///////////////////////////////////////////////////////////
void MainWindow::onTraiterTag(QString tag) {
    qDebug() << QThread::currentThreadId()
            << Q_FUNC_INFO;

    if (!traitement(tag)){
        qDebug() << QThread::currentThreadId()
                << Q_FUNC_INFO
                << "Pb trame !"
                << tag;
    } // if decode
} // method

///////////////////////////////////////////////////////////
void MainWindow::onGererThread()
{
    qDebug() << QThread::currentThreadId()
            << Q_FUNC_INFO;
    T_Thread *th;
    QString adr;

    th = new T_Thread;
    cl = serv->nextPendingConnection();
    adr = cl->peerAddress().toString();
    th->noLect = 0; // retrouve le no en fonction de l'adresse
    cl->readAll(); // vide le buffer
    th->thcl = new CThreadClient(this,cl);  // mémorisation dans la liste des lecteurs
    connect(th->thcl, SIGNAL(terminated()), this, SLOT(onEffacerUnThread()));
    connect(th->thcl, SIGNAL(dataLue(QString)), this, SLOT(onTraiterTag(QString)));
    th->thcl->start();
    lecteurs.append(th);  // ajout a la liste de mémorisation des lecteurs
    nbLect++;// maj BDD
} // MainWindow::method

void MainWindow::on_menuQuitter_triggered()
{
    qDebug() << QThread::currentThreadId()
            << Q_FUNC_INFO
            << "Avant this->close();";
    this->close(); // termine l'application
} // method

