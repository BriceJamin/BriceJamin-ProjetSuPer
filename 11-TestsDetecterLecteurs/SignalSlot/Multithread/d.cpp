#include "d.h"
#include <QDebug>
#include <QThread>

D::D() : QObject()
{}

void D::slot_D()
{
    qDebug() << Q_FUNC_INFO
            << QThread::currentThreadId()
            << "Signal C::sig_C() recu";
    emit sig_D();
}
