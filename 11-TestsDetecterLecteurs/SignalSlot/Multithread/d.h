#ifndef D_H
#define D_H

#include <QObject>

class D : public QObject
{
    Q_OBJECT
signals:
    void sig_D();
public slots:
    void slot_D();
public:
    D();
};

#endif // D_H
