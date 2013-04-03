#ifndef A_H
#define A_H

#include <QObject>

class A : public QObject
{
    Q_OBJECT
signals:
    void sig_A();
public:
    A();
    void start();
};

#endif // A_H
