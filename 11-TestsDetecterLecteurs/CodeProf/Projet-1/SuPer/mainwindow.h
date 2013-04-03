#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QLabel>
#include <QTimer>

#include "cihmpersonne.h"
#include "cihmcamera.h"
#include "cihmlecteur.h"
#include "cihmbadge.h"
#include "cihmaffecter.h"
#include "commun.h"
#include "cthreadclient.h"
#include "cihmparametrer.h"

//#include "cmsg.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_menuQuitter_triggered();

public slots:
    void onGererThread();
    void onTraiterTag(QString tag);
    void onEffacerUnThread();

private:
    Ui::MainWindow *ui;
    bool traitement(QString &trame);
    void toutEteindreIhm();
    int calculerMoyenne(T_ListeLabel *tll);
    void calculerDroite(int sens, T_Point pointA, T_Point pointB, T_Point *pointF);
    void sensDePassage(T_ListeLabel *tll);

    QTcpServer *serv;
    QTcpSocket *cl;
    bool appli; // si SuPer doit continuer après identification.
    QList<T_ListeLabel *> listeLabel;
    QList<T_Thread *> lecteurs;   // pointeur vers les différents lecteurs
    quint64 nbT; // compte le nbre de trame recu
    int nbB;
    quint8 nbLect;  // nombre de lecteur connectés
    int vue;   // image affichée sur lfond
    QTimer *aff;
    T_Config config;
//    CMsg *msg; // classe gérant la file de message
};

#endif // MAINWINDOW_H

