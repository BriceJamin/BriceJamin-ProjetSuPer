#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "person.h"
#include "persondialog.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(bdd.isOpen())
        ui->lineEdit->setText("bdd ok");
    else
        ui->lineEdit->setText("erreur bdd");
    //_personTupleView = new PersonTupleView();
    //_personTupleView->setVisible(true);
    //QString chaine = PersonTupleView::methodeTest();
    //ui->lineEdit->setText(chaine);
    //PersonDialog *personDialog = new PersonDialog(this);
    //personDialog->setVisible(true);
    /*_layout = new QHBoxLayout(this);
    _layout->addWidget(_personTupleView);
    this->setLayout(_layout);
    //personTupleView->show(); */
    //_testLayout = new TestLayout();
    //_testLayout->setVisible(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
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

void MainWindow::on_addPersonPushButton_clicked()
{
    Person person = PersonDialog::getNewPersonInput();
    qDebug() << person.name()
                << person.firstname()
                << person.startDate()
                << person.endDate()
                << person.company()
                << person.photo();
}
