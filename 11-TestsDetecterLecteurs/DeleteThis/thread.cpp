#include "thread.h"
#include <QDebug>

Thread::Thread(QObject *parent) :
    QThread(parent)
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
}

Thread::~Thread()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "avant quit()";
    quit();
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "après quit()";
}

void Thread::run()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
    exec();
}
