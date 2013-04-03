#include "a.h"

A::A(int a) : QObject(), _a(a)
{}

int A::a() const
{
    return _a;
}

QDebug operator<<(QDebug qDebug, const A& a)
{
    return qDebug.nospace() << a.a();
}
