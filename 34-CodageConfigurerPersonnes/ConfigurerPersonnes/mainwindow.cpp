#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _personTupleView = new PersonTupleView();
    _personTupleView->setVisible(true);
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
