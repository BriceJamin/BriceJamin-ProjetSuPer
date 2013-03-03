#include "readerdetector.h"

ReaderDetector::ReaderDetector(QObject *parent) :
    QObject(parent)
{
}

void ReaderDetector::on(QString address, unsigned int port){}
void ReaderDetector::off(){}


