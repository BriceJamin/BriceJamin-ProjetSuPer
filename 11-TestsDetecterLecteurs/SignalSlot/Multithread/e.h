#ifndef E_H
#define E_H

#include <QObject>

class E : public QObject
{
    Q_OBJECT
signals:
    void sig_E1();
    void sig_finishedE();
public slots:
    void slot_E1();
    void slot_E2();
public:
    E(QObject*);
    ~E();
};

#endif // E_H
