#include "detecterlecteurs.h"
#include "ui_detecterlecteurs.h"

DetecterLecteurs::DetecterLecteurs(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DetecterLecteurs)
{
    ui->setupUi(this);
}

DetecterLecteurs::~DetecterLecteurs()
{
    delete ui;
}

void DetecterLecteurs::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DetecterLecteurs::on_pbOn_clicked()
{
    /* TODO : Connecter le serveur */
}

void DetecterLecteurs::on_pbOff_clicked()
{
    /* TODO : Déconnecter le serveur */
}
