#ifndef B_H
#define B_H

#include <QObject>

class B : public QObject
{
    Q_OBJECT
public slots:
    void slot_B();
public:
    B();
};

#endif // B_H
