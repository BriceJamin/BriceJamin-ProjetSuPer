#include "b.h"
#include <QDebug>
#include <QThread>

B::B() : QObject()
{}

void B::slot_B()
{
    qDebug() << Q_FUNC_INFO
            << QThread::currentThreadId()
            << "Signal A::sig_A() recu";
    emit sig_B();
}
