#include <QtGui/QApplication>
#include "detecterlecteurs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DetecterLecteurs w;
    w.show();
    return a.exec();
}
