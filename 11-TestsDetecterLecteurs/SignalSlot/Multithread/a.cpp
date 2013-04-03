#include "a.h"
#include <QDebug>
#include <QThread>

A::A() : QObject()
{}

void A::start()
{
    qDebug() << Q_FUNC_INFO
            << QThread::currentThreadId()
            << "Avant emit sig_A()";

    emit sig_A();

    qDebug() << Q_FUNC_INFO
            << QThread::currentThreadId()
            << "Apres emit sig_A() et avant boucle infinie";

     // Boucle infinie
    for(;;);

    // Ne sera jamais exécuté
    qDebug() << Q_FUNC_INFO
            << QThread::currentThreadId()
            << " : Après boucle infinie";
}
