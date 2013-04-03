#ifndef B_H
#define B_H

#include <QObject>
#include "a.h"

typedef A MyType;

class B : public QObject
{
Q_OBJECT
public:
    explicit B(QObject *parent = 0);

signals:

public slots:
    void slot(MyType*);
};

#endif // B_H
