#ifndef FILS_H
#define FILS_H

#include <QObject>

class Fils : public QObject
{
Q_OBJECT
public:
    explicit Fils(QObject *parent = 0);
    ~Fils();
};

#endif // FILS_H
