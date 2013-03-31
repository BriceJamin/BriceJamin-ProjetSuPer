#include "a.h"
#include <QDebug>
#include <QThread>

A::A(QObject *parent) :
    QObject(parent)
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
}

A::~A()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
}

void A::run()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "avant finished";
    emit finished();
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "après finished";
}
