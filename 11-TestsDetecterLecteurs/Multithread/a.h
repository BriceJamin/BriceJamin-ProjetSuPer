#ifndef A_H
#define A_H

#include <QObject>

class A : public QObject
{
Q_OBJECT
signals:
    void finished();
public:
    explicit A(QObject *parent = 0);
    ~A();

public slots:
    void run();
    void stop();
};

#endif // A_H
