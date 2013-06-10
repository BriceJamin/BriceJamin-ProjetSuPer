#include <QtTest/QtTest>
#include "testperson.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TestPerson testPerson;
    QTest::qExec(&testPerson, argc, argv);

    return 0;
}
