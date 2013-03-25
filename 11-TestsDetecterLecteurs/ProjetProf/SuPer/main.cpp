#include <QtGui/QApplication>
#include "fident.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug(); // Pour que les debugs commencent sur une nouvelle ligne
    FIdent w;
    w.show();

    return a.exec();
}
