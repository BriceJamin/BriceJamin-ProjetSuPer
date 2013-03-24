#include "fils.h"
#include <QDebug>

Fils::Fils(QObject *parent) :
    QObject(parent)
{}

 Fils::~Fils()
 {
     qDebug() << Q_FUNC_INFO;
 }
