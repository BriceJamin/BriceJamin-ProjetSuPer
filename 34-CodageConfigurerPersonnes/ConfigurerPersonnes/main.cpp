#include <QApplication>
#include "mainwindow.h"
#include <QTextCodec>
#include <QDebug>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    qDebug();
    MainWindow w;
    w.show();
    return a.exec();
}
