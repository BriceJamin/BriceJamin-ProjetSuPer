#include "a.h"
#include <QDebug>

A::A() : QObject()
{}

void A::start()
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "Avant emit sig_A()";

    // Est emis immédiatement
    emit sig_A();

    qDebug() << "Apres emit sig_A() et avant boucle infinie";
    for(;;); // Boucle infinie

    // Ne sera jamais exécuté
    qDebug() << "Après boucle infinie";
}
