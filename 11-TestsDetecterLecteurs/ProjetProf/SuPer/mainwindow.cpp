#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) ,
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // pour le menu
    ihmAffecter = new CIhmAffecter();
    ihmPersonne = new CIhmPersonne();
    ihmLecteur = new CIhmLecteur();
    ihmBadge = new CIhmBadge();
    ihmCamera = new CIhmCamera();
    ihmParametrer = new CIhmParametrer();
    connect(ui->actionBadgesAffecter, SIGNAL(triggered()), this, SLOT(on_menuBadgesAffecter()));
    connect(ui->actionGerer_les_personnes, SIGNAL(triggered()), this, SLOT(on_menuGerer_les_personnes_triggered()));
    connect(ui->actionGerer_les_badges, SIGNAL(triggered()), this, SLOT(on_menuGerer_les_badges_triggered()));
    connect(ui->actionGerer_les_cameras, SIGNAL(triggered()), this, SLOT(on_menuGerer_les_cameras_triggered()));
    connect(ui->actionGerer_les_lecteurs, SIGNAL(triggered()), this, SLOT(on_menuGerer_les_lecteurs_triggered()));
    connect(ui->actionParametrer, SIGNAL(triggered()), this, SLOT(on_menuParametrer_triggered()));
    vue=0; // pour les coordonnées d'affichage
    ui->twOnglets->setCurrentIndex(0);

    nbT = 0;   // nbre de trame
    nbB = 0;   // nbre de badges
    nbLect=0; // aucun lecteur connecté

    // pour le réseau
    serv = new QTcpServer(this);
    serv->listen(QHostAddress::Any, 2222);
    connect(serv, SIGNAL(newConnection()), this, SLOT(onGererThread()));
    ui->teRecu->append(QString::fromUtf8("Serveur en écoute des lecteurs."));
    // timer d'actualisation de l'affichage
    aff = new QTimer(this);
    connect(aff, SIGNAL(timeout()), this, SLOT(on_affichage()));
    aff->start(config.tempoA);

//    // pour la file de message
//    msg = new CMsg(this);

} // method

MainWindow::~MainWindow()
{
    delete ihmAffecter;
    delete ihmPersonne;
    delete ihmLecteur;
    delete ihmBadge;
    delete ihmCamera;
    delete serv;
    while (!listeLabel.isEmpty()) {
        T_ListeLabel *tll = listeLabel.takeFirst();
        delete tll->l;
        delete tll->wdm;
        for(int i=0 ; i<config.maxLect ; i++)
            if (tll->wdr[i])
                delete tll->wdr[i];
        delete tll;
        delete listeLabel.takeFirst();
    } // while
    T_Thread *th;
    while (!lecteurs.isEmpty()) {
        th = lecteurs.takeFirst();
        delete th->thcl;
        delete th;
    } // while
    lecteurs.clear();
    delete aff;
    delete ui;
    //    delete msg;
} // method

/////////////////////////////////////////////////////////////
void MainWindow::afficherLecteur(int noL, bool etat)
{
    switch(noL) {
      case 1: ui->lLectCon->setEnabled(etat); break;
      case 2: ui->lLectServGen->setEnabled(etat); break;
      case 3: ui->lLectGAS->setEnabled(etat); break;
      case 4: ui->lLectCaps->setEnabled(etat); break;
      default: break;
    } // sw
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
            ui->teRecu->append("Pb de communication avec le lecteur "+QString("%1").arg(th->noLect));
            delete th->thcl;
            delete th;
            lecteurs.removeAt(i);
            nbLect--;
            ui->lNbL->setText(QString("%1").arg(nbLect));
            break;
        } // if finish
    } // for
} // method

///////////////////////////////////////////////////////////
// return true si trame au bon format
bool MainWindow::traitement(QString &trame) {
 QString noBadge, sens, lect, mouv;
 T_ListeLabel *tll;

 nbT++; // compteur de trames

 // séparation des parties de la trame
 noBadge = trame.mid(3,3);
 if (noBadge == "000") {
     qDebug("Mauvais badge.");
     //qDebug(trame.toLocal8Bit().data());
     ui->teRecu->append("Mauvais badge no=000");
     return false;
 } // if noB
 sens = trame.mid(1,2);
 mouv = trame.mid(6,3);
 lect = trame.mid(9,2);
 //qDebug(mouv.toLocal8Bit().data());
 int inoLect = lect.toInt(0,16);  // conversion

 // le badge existe-t-il dans la BDD ?
// oui par défaut

 // le badge est-il représenté sur l'IHM ?
// oui par défaut

 // creation label si existe pas
// non pas besoin

 tll->noLect = inoLect;

 tll->etat |= MOUV0;   // mouv=0
 // relance du timer si mouvement, réception et affichage
 if (mouv.toInt(0,16) > 0 ) {  // si mouvement
     tll->etat &= ~MOUV;    // alarme mouvement
     tll->etat &= ~MOUV0;   // un seul mouvement
     tll->wdm->setSingleShot(true);
     tll->wdm->start(config.tempoM); //  ms
 } // if mouvement

 // réarmer le timer REC, le créer si nouveau lecteur
 tll->etat &= ~REC;
 if (!tll->wdr[inoLect]) {
     tll->wdr[inoLect] = new QTimer(this);
     connect(tll->wdr[inoLect], SIGNAL(timeout()), this, SLOT(onTimerRec()));
 } // si création timer wdr
 tll->wdr[inoLect]->setSingleShot(true);
 tll->wdr[inoLect]->start(config.tempoR);

 // recherche identité
 // donnée par défaut
 tll->pers.nom = "No Bdd";
 tll->pers.pnom = "No Bdd";
 tll->pers.societe = "No Bdd";
 tll->pers.noPers = 0;

 // calcul de la moyenne de la sensibilité
 // non pas besoin

 // recherche position affichage
 // non pas besoin

 // affichage ihm
 ui->teRecu->append(" S:"+sens+" B:"+noBadge+" M:"+mouv+" L:"+lect+" "+trame);

 return true;
}

///////////////////////////////////////////////////////////////
void MainWindow::on_affichage()   // toutes les TEMPOA ms
{
    // ne rien faire
} // method


///////////////////////////////////////////////////////////////
void MainWindow::sensDePassage(T_ListeLabel *tll)
{
    // pour l'instant, une seule zone
    if (tll->sdp[tll->noLect] < tll->memSdp[tll->noLect])
        tll->etat &= ~AR;  // retour
    if (tll->sdp[tll->noLect] > tll->memSdp[tll->noLect])
        tll->etat |= AR;  // aller
    if (tll->sdp[tll->noLect] != tll->noLect)
        tll->memSdp[tll->noLect] = tll->sdp[tll->noLect];

    // détermination de la zone contigüe
    if (tll->sdp[tll->noLect]>0)
        tll->zone = tll->noLect;
    if (tll->sdp[tll->noLect+1]>0)
        tll->zone = tll->noLect*11+1;
    if (tll->sdp[tll->noLect-1]>0)
        tll->zone = (tll->noLect-1)*11+1;
    ui->lZone->setText(QString("Zone %1").arg(tll->zone));
} // method

///////////////////////////////////////////////////////////////
void MainWindow::calculerDroite(int sens, T_Point pointA, T_Point pointB, T_Point *pointF)
{
    float dx, dy, a, x, y;

    dx = pointB.x - pointA.x;
    dy = pointB.y - pointA.y;

    x = sens*dx/100;  // mise à l'échelle
    a = dy/dx;     // coeff directeur, pas d'ordonnée à l'origine car changement de repère
    y = a*x;   // équation de la droite
    pointF->x = pointA.x + x;
    pointF->y = pointA.y + y;
} // methode



///////////////////////////////////////////////////////////////
int MainWindow::calculerMoyenne(T_ListeLabel *tll)
{
    // calcul de la moyenne de la sensibilité
    int sumMoy=0;
    for (int i=0 ; i<config.maxVal ; i++)
        sumMoy += tll->moySens[tll->noLect][i];
    return sumMoy / config.maxVal;

} // method

///////////////////////////////////////////////////////////
void MainWindow::onTimerMouv() {
    T_ListeLabel *tll;
    int nbB = listeLabel.size();
    for (int i=0 ; i<nbB ; i++) {
        tll = listeLabel.at(i);
        if (!tll->wdm->isActive()) {
            tll->etat |= MOUV;   // homme en danger
        } // if trouvé
    } // for
} // method

///////////////////////////////////////////////////////////
void MainWindow::onTimerRec() {
    // ne rien faire
} // method

///////////////////////////////////////////////////////////
void MainWindow::onFinConnexionClient() {
} // method


///////////////////////////////////////////////////////////
void MainWindow::onTraiterTag(QString tag) {
    if (!traitement(tag)){
        qDebug("Pb trame !");
           ui->teRecu->append(tag);
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
    ui->teRecu->append(adr);
    th->noLect = 0; // retrouve le no en fonction de l'adresse
    cl->readAll(); // vide le buffer
    th->thcl = new CThreadClient(this,cl);  // mémorisation dans la liste des lecteurs
    connect(th->thcl, SIGNAL(terminated()), this, SLOT(onEffacerUnThread()));
    connect(th->thcl, SIGNAL(dataLue(QString)), this, SLOT(onTraiterTag(QString)));
    th->thcl->start();
    lecteurs.append(th);  // ajout a la liste de mémorisation des lecteurs
    nbLect++;// maj BDD
    // IHM
    ui->lNbL->setText(QString("%1").arg(nbLect));
    afficherLecteur(th->noLect, true);
} // MainWindow::method

void MainWindow::toutEteindreIhm() {
/*    T_ListeLabel *tll;
    int nbB = listeLabel.size();

    for (int i=0 ; i<nbB ; i++) {
      tll = listeLabel.at(i);
      tll->l->setVisible(false);
    } // for
*/
} // method

/////////////////////////////////////////////////////////////
void MainWindow::on_menuBadgesAffecter()
{
    ihmAffecter->show();
} // method

void MainWindow::on_menuParametrer_triggered()
{
    ihmParametrer->show(); // termine l'application
} // method

void MainWindow::on_menuQuitter_triggered()
{
    this->close(); // termine l'application
} // method

void MainWindow::on_menuGerer_les_personnes_triggered()
{
    ihmPersonne->show();
} // method

void MainWindow::on_menuGerer_les_lecteurs_triggered()
{
//    ihmLecteur->show();
} // method

void MainWindow::on_menuGerer_les_badges_triggered()
{
//    ihmBadge->show();
} // method

void MainWindow::on_menuGerer_les_cameras_triggered()
{
//    ihmCamera->show();
} // method

void MainWindow::on_tbVueC_clicked()
{
// ui->twOnglets->setCurrentIndex(1);
// vue=1;
}

void MainWindow::on_tbVueSG_clicked()
{
//  ui->twOnglets->setCurrentIndex(2);
//  vue=2;
}

void MainWindow::on_tbVueGAS_clicked()
{
//  ui->twOnglets->setCurrentIndex(3);
//  vue=3;
}

void MainWindow::on_tbVueCapsule_clicked()
{
//  ui->twOnglets->setCurrentIndex(4);
//  vue=4;
}

void MainWindow::on_pbRetour_clicked()
{
  ui->twOnglets->setCurrentIndex(0);
  vue=0;
}

void MainWindow::on_twOnglets_currentChanged(int index)
{
} // method
