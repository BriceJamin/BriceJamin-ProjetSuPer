#ifndef F_H
#define F_H

#include <QObject>

class F : public QObject
{
    Q_OBJECT
signals:
    void sig_F();
    void sig_finishedF();
public slots:
    void slot_startF();
    void slot_F();
public:
    F(QObject*);
    ~F();
};

#endif // F_H
