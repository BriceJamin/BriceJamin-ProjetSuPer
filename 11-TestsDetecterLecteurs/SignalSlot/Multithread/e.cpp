#include "e.h"
#include <QDebug>
#include <QThread>

E::E(QObject* parent) : QObject(parent)
{}

E::~E()
{
    qDebug() << QThread::currentThreadId()
            << Q_FUNC_INFO;
}

void E::slot_E1()
{
    qDebug() << QThread::currentThreadId()
            << Q_FUNC_INFO
            << "E::sig_E1 vers F::slot_F";

    emit sig_E1();
}

void E::slot_E2()
{
    qDebug() << QThread::currentThreadId()
            << Q_FUNC_INFO
            << "E::sig_finishedE vers E::deleteLater";
    emit sig_finishedE();
}
