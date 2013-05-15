#include "thread.h"
#include <QDebug>

Thread::Thread(QObject *parent) :
    QThread(parent)
{ qDebug() << QThread::currentThreadId() << Q_FUNC_INFO; }

Thread::~Thread()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "quit()";
    quit();
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "wait()";
    bool finished = wait();
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "finished" << finished;
}

void Thread::run()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
    exec();
}
