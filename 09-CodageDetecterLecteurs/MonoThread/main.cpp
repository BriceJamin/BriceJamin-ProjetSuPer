#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server server("127.0.0.254", 43210);
    MainWindow w(&server);
    w.show();
    
    return a.exec();
}
