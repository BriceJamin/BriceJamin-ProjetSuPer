#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug();

    Server server("127.0.0.254", (quint16)43210);
    MainWindow w(&server);
    w.show();
    
    return a.exec();
}
