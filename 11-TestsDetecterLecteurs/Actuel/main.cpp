#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug();

    Server server("192.168.60.100", "2222");
    MainWindow w1(&server);
    //MainWindow w2(&server);
    w1.show();
    //w2.show();
    
    return a.exec();
}
