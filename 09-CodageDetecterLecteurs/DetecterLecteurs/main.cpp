#include <QtGui/QApplication>
#include "detecterlecteurs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ReaderDetector* rd = new ReaderDetector();
    DetecterLecteurs w(rd);
    delete rd;
    w.show();
    return a.exec();
}
