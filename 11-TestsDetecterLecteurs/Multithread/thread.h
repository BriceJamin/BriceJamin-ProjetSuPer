#ifndef THREAD_H
#define THREAD_H
#include <QThread>
class Thread : public QThread
{
Q_OBJECT
public:
    Thread(QObject *parent = 0);
    ~Thread();
    void run();
};
#endif // THREAD_H
