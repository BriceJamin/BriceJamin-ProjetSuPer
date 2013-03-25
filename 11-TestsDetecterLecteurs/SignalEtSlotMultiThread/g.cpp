#include "g.h"
#include <QDebug>
#include <QThread>

G::G(QObject* parent) : QObject(parent)
{}

G::~G()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
}

void G::slotG_H_started()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
}

void G::slotG_H_finished()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
}
