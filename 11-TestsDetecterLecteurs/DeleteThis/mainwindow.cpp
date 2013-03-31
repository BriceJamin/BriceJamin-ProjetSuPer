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
}

void MainWindow::changeEvent(QEvent *e)
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
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
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;

    // Création
    Thread* thread = new Thread();
    A* a = new A();

    // MoveTo
    a->moveToThread(thread);

    // Connexion

    // Suivi cursus de vie du thread
    this->connect(thread, SIGNAL(started()), SLOT(thread_started()));
    this->connect(thread, SIGNAL(finished()), SLOT(thread_finished()));
    this->connect(thread, SIGNAL(destroyed()), SLOT(thread_destroyed()));
    this->connect(thread, SIGNAL(terminated()), SLOT(thread_terminated()));

    // Thread::start() déclenche a::run()
    a->connect(thread, SIGNAL(started()), SLOT(run()));

    // a::finished() déclenchera sa mort
    a->connect(a, SIGNAL(finished()), SLOT(deleteLater()));

    // La destruction de a déclenchera l'arrêt du thread
    thread->connect(a, SIGNAL(destroyed()), SLOT(quit()));

    // Appui sur Kill them All arretera a
    a->connect(ui->killThemAllPushButton, SIGNAL(clicked()), SLOT(stop()));

    // Lancement du thread
    thread->start();
}

void MainWindow::thread_destroyed()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
}

void MainWindow::thread_finished()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
}

void MainWindow::thread_started()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
}

void MainWindow::thread_terminated()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
}

void MainWindow::a_destroyed()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
}
