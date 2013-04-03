#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(signal(MyType*)), this, SLOT(slot(MyType*)));
    connect(this, SIGNAL(signal(MyType*)), &b, SLOT(slot(MyType*)));
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

void MainWindow::on_pushButton_clicked()
{
    qDebug() << Q_FUNC_INFO;

    QThread* qThread = new QThread;
    MyType* myType = new MyType(7);

    b.moveToThread(qThread);

    qThread->start();

    emit signal(myType);
}

 void MainWindow::slot(MyType* myType)
 {
     qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << *myType;
 }
