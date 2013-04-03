#include "f.h"
#include <QDebug>
#include <QThread>

F::F(QObject* parent) : QObject(parent)
{}

F::~F()
{
    qDebug() << QThread::currentThreadId()
            << Q_FUNC_INFO;
}

void F::slot_startF()
{
    qDebug() << QThread::currentThreadId()
            << Q_FUNC_INFO
            << "F::sig_F vers E::slot_E1";
    emit sig_F();
}

void F::slot_F()
{
    qDebug() << QThread::currentThreadId()
            << Q_FUNC_INFO
            << "F::sig_finishedF vers E::slot_E2, F::deleteLater, QThread::quit";
    emit sig_finishedF();
}
