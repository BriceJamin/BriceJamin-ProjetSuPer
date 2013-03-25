#ifndef H_H
#define H_H

#include <QObject>
#include <QThread>

class H : public QObject
{
    Q_OBJECT
signals:
    void sigH_started();
    void sigH_finished();
public slots:
    void slotH_start();
public:
    H();
    ~H();
private slots:
    void slotH_work();
private:
    QThread thread;
};

#endif // H_H
