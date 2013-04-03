#ifndef THREAD_H
#define THREAD_H

#include <QThread>

class Thread : public QThread
{
Q_OBJECT
public:
    explicit Thread(QObject *parent = 0);
    ~Thread();
    void run();

signals:

public slots:

};

#endif // THREAD_H
