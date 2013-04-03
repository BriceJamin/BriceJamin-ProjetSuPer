#ifndef A_H
#define A_H

#include <QDebug>

class A : public QObject
{
    Q_OBJECT
public:
    A(int a=0);
    int a() const;
private:
    int _a;
};

QDebug operator<<(QDebug, const A&);

#endif // A_H
