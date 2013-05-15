#include "a.h"
#include <QDebug>
#include <QThread>

A::A() : QObject(), _i(0)
{ qDebug() << QThread::currentThreadId() << Q_FUNC_INFO; }

A::~A()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
    if(_i)
        delete _i;
}

void A::start()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "parent() :" << parent();
    _i = new int;
    for(*_i=0; *_i<=5; (*_i)++)
    {
        qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << *_i;
        sleep(1);
    }
}
