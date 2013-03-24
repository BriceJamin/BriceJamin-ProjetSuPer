#ifndef C_H
#define C_H

#include <QObject>

class C : public QObject
{
    Q_OBJECT
signals:
    void sig_C();
public slots:
    void slot_C();
    void slot_CLibre();
public:
    C();
};

#endif // C_H
