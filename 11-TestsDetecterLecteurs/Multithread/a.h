#ifndef A_H
#define A_H
#include <QObject>
class A : public QObject
{
Q_OBJECT
public:
    A();
    ~A();
public slots:
    void start();
private:
    int* _i;
};
#endif // A_H
