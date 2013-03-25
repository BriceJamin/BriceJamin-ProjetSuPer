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
    qDebug() << "Serveur en écoute des lecteurs.";
} // method

MainWindow::~MainWindow()
{
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
    T_Thread *th;
    int nb;

    nb = lecteurs.size();
    for (int i=0 ; i<nb ; i++) {
        th = lecteurs.at(i);
        if (th->thcl->isFinished()) {
            afficherLecteur(th->noLect, false);
            qDebug() << "Pb de communication avec le lecteur :"
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
 QString noBadge, sens, lect, mouv;

 nbT++; // compteur de trames

 // séparation des parties de la trame
 noBadge = trame.mid(3,3);
 if (noBadge == "000")
 {
     qDebug("Mauvais badge.");
     qDebug() << "Mauvais badge no=000";
     return false;
 }
 sens = trame.mid(1,2);
 mouv = trame.mid(6,3);
 lect = trame.mid(9,2);

 // affichage ihm
 qDebug() << "S:" << sens
         << " B:" << noBadge
         << " M:" << mouv
         << " L:" << lect
         << trame;

 return true;
}

///////////////////////////////////////////////////////////
void MainWindow::onTraiterTag(QString tag) {
    if (!traitement(tag)){
        qDebug("Pb trame !");
           qDebug() << tag;
    } // if decode
} // method

///////////////////////////////////////////////////////////
void MainWindow::onGererThread()
{
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
    this->close(); // termine l'application
} // method

