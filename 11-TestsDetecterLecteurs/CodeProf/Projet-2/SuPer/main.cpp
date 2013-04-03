#include <QtGui/QApplication>
#include "fident.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug();
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
    FIdent w;
    w.show();

    return a.exec();
}
