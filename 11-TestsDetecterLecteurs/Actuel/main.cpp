#include <QApplication>
#include "mainwindow.h"
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    qDebug();

    Server server("192.168.60.100", "2222");
    MainWindow w1(&server);
    //MainWindow w2(&server);
    w1.show();
    //w2.show();
    
    return a.exec();
}
