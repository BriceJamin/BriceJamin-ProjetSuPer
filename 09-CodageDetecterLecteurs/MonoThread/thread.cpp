#include "thread.h"
#include <QDebug>

Thread::Thread(QObject *parent) :
    QThread(parent)
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;

    // Suivi cursus de vie du thread
    this->connect(this, SIGNAL(started()), SLOT(slot_started()));
    this->connect(this, SIGNAL(finished()), SLOT(slot_finished()));
    this->connect(this, SIGNAL(destroyed()), SLOT(slot_destroyed()));
    this->connect(this, SIGNAL(terminated()), SLOT(slot_terminated()));

    // L'arrêt du thread déclenchera sa mort
    this->connect(this, SIGNAL(finished()), SLOT(deleteLater()));
    // TODO : Traiter de la même façon le signal terminated ?
}

Thread::~Thread()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
    //qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "avant quit()";
    //quit();
    //qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "apres quit()";
}

void Thread::run()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
    exec();
}

void Thread::slot_started()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
}

void Thread::slot_finished()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
}

void Thread::slot_destroyed()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
}

void Thread::slot_terminated()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
}
