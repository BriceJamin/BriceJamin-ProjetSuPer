#include "c.h"
#include <QDebug>
#include <QThread>

C::C() : QObject()
{}

void C::slot_C()
{
    qDebug() << Q_FUNC_INFO
            << QThread::currentThreadId()
            << "Avant emit sig_C()";

    emit sig_C();

    qDebug() << Q_FUNC_INFO
            << QThread::currentThreadId()
            << "Apres emit sig_C() et avant boucle infinie";

     // Boucle infinie
    for(;;);

    // Ne sera jamais exécuté
    qDebug() << Q_FUNC_INFO
            << QThread::currentThreadId()
            << " : Après boucle infinie";
}

void C::slot_CLibre()
{
    qDebug() << Q_FUNC_INFO
            << QThread::currentThreadId();
}
