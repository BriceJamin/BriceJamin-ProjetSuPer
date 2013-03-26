#include "h.h"
#include <QDebug>

H::H() : QObject()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "this->moveToThread(&thread);";

    this->moveToThread(&thread);
    this->connect(&thread, SIGNAL(started()), SLOT(slotH_work()));
    thread.connect(this, SIGNAL(sigH_finished()), SLOT(quit()));
    thread.connect(this, SIGNAL(destroyed()), SLOT(quit()));

    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "thread.start();";

    //thread.start();

    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "apres thread.start();" ;
}

H::~H()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "thread.wait();";
    thread.wait();
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "fin";
}

void H::slotH_start()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "thread.start();"; //  vers G::slot_G1
    thread.start();
}

void H::slotH_work()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "emit sigH_started();";
    emit sigH_started();

    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "emit sigH_finished();";
    emit sigH_finished();
}
