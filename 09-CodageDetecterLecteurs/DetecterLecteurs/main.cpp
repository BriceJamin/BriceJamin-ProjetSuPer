#include <QtGui/QApplication>
#include "detecterlecteurs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ReaderDetector rd;
    DetecterLecteurs w(&rd);
    w.show();
    return a.exec();
}
