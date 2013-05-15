#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "a.h"
#include "thread.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
    delete ui;

    while (!threadList.isEmpty())
    {
        Thread* thread = threadList.takeFirst();
        qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "delete"  << thread;
        delete thread;
    }

    while (!aList.isEmpty())
        delete aList.takeFirst();
}

void MainWindow::on_pushButton_clicked()
{
    Thread* thread = new Thread(this);
    A* a = new A();
    threadList.append(thread);
    aList.append(a);

    a->moveToThread(thread);
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << thread << "a->parent:" << a->parent();
    a->connect(thread, SIGNAL(started()), SLOT(start()));
    a->connect(this, SIGNAL(sig_killA()), SLOT(deleteLater()));

    thread->start();
}
