#include "thread.h"

Thread::Thread(QObject *parent) :
    QThread(parent)
{
}

 void Thread::run()
 {
     exec();
 }
