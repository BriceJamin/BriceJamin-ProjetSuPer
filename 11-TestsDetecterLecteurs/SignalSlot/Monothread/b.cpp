#include "b.h"
#include <QDebug>

B::B() : QObject()
{}

void B::slot_B()
{
    qDebug() << Q_FUNC_INFO;
}
