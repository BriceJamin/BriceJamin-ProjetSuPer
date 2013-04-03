#include "b.h"
#include <QThread>

B::B(QObject *parent) :
    QObject(parent)
{
}

void B::slot(MyType* myType)
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << *myType;
}
