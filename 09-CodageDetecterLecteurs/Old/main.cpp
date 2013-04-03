#include <QtGui/QApplication>
#include "detecterlecteurs.h"
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Thread principal : " << QThread::currentThreadId();
    ReaderDetector rd;
    DetecterLecteurs w(&rd);
    w.show();
    return a.exec();
}
