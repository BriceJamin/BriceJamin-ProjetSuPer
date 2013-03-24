#include <QtCore>
#include "a.h"
#include "b.h"
#include "c.h"
#include "d.h"
#include "e.h"
#include "f.h"

// Peut contenir des erreurs, l'ignorer
void test1(QCoreApplication* app)
{
    A a; B b;

    b.connect(&a, SIGNAL(sig_A()), SLOT(slot_B()));

    // Le slot quit() ne sera jamais appelé car
    //  le thread de ce slot est occupé : boucle infinie
    //  déclenchée dans A::start()
    app->connect(&b, SIGNAL(sig_B()), SLOT(quit()));

    QThread threadB;
    threadB.connect(&b, SIGNAL(sig_B()), SLOT(quit()));

    b.moveToThread(&threadB);
    threadB.start();

    a.start();
    /*
      Affiche :
void A::start() 3071669968 Avant emit sig_A()
void A::start() 3071669968 Apres emit sig_A() et avant boucle infinie
void B::slot_B() 3070139248 Signal A::sig_A() recu
(Obligé de fermer manuellement l'application.)
      */
    /*
      Conclusion :
      *  La connexion des signaux slots s'effectue correctement.
      *  L'exécution des slots s'effectue dans les bons threads.
      *  Un signal n'exécute un slot que si le thread du recepteur
        est libre.
      */
}

// Peut contenir des erreurs, l'ignorer
void test2(QCoreApplication* app)
{
    // Est-ce que slot_C() va être réexécuté
    // alors qu'il est déjà en cour d'exécution ?
    // => NON : Le thread est occupé

    // Est-ce que le slot slot_CLibre() va être exécuté alors que le
    // thread est occupé dans slot_C() ?
    // => NON : Le thread est occupé
    C c; D d;

    d.connect(&c, SIGNAL(sig_C()), SLOT(slot_D()));
    c.connect(&d, SIGNAL(sig_D()), SLOT(slot_C()));
    c.connect(&d, SIGNAL(sig_D()), SLOT(slot_CLibre()));

    app->connect(&d, SIGNAL(sig_D()), SLOT(quit()));

    QThread threadD;
    threadD.connect(&c, SIGNAL(sig_C()), SLOT(quit()));

    d.moveToThread(&threadD);
    threadD.start();

    c.slot_C();
    /*
      Affiche :
void C::slot_C() 3070990032 Avant emit sig_C()
void C::slot_C() 3070990032 Apres emit sig_C() et avant boucle infinie
void D::slot_D() 3069459312 Signal C::sig_C() recu
(Obligé de fermer manuellement l'application.)
      */
}

// Fonctionnel, le prendre en exemple
// Pourrait être rendu plus simple d'utilisation
//  en préconnectant certains signaux et slots au
//  sein même des classes
void test3(QCoreApplication* app)
{
    // C'est au nouveau thread F de communiquer vers
    //  le thread principal E dans le cadre de notre projet :
    // QThread::started -> F::slot_startF -> F::sig_F -> E::slot_E1 -> E::sig_E1 -> F::slot_F -> F::sig_finishedF
    // F::sig_finishedF -> E::slot_E2
    // F::sig_finishedF -> F::deleteLater
    // F::sig_finishedF -> QThread::quit
    // QThread::finished -> QThread::deleteLater
    // QThread::terminated -> QThread::deleteLater

    // Pas d'instanciation statique car sinon ils meurent
    //  à la fin de cette fonction et ne pourront plus communiquer
    E* e = new E(0);
    // Pas de parent car sinon impossible de le moveToThread
    F* f = new F(0);
    QThread* threadF = new QThread();
    f->moveToThread(threadF);

    // Connexions pour le scenario
    // QThread::started -> F::slot_startF
    f->connect(threadF, SIGNAL(started()), SLOT(slot_startF()));
    // F::sig_F -> E::slot_E1
    e->connect(f, SIGNAL(sig_F()), SLOT(slot_E1()));
    // E::sig_E1 -> F::slot_F
    f->connect(e, SIGNAL(sig_E1()), SLOT(slot_F()));
    // F::sig_finishedF -> E::slot_E2
    e->connect(f, SIGNAL(sig_finishedF()), SLOT(slot_E2()));

    // Connexions pour libérer la mémoire de E et F
    // E::sig_finishedE -> E::deleteLater
    e->connect(e, SIGNAL(sig_finishedE()), SLOT(deleteLater()));
    // F::sig_finishedF -> F::deleteLater
    f->connect(f, SIGNAL(sig_finishedF()), SLOT(deleteLater()));

    // Connexion pour arrêter le thread et laisser le temps à F de se détruire
    // F::sig_finishedF -> QThread::quit Pose problème (?) F n'a parfois pas le temps de se détruire
    // threadF->connect(f, SIGNAL(sig_finishedF()), SLOT(quit()));
    // F::destroyed -> QThread::quit Résoud le problème (?)
    threadF->connect(f, SIGNAL(destroyed()), SLOT(quit()));

    // Connexions pour libérer la mémoire de QThread
    // QThread::finished -> QThread::deleteLater
    threadF->connect(threadF, SIGNAL(finished()), SLOT(deleteLater()));
    // QThread::terminated -> QThread::deleteLater
    threadF->connect(threadF, SIGNAL(terminated()), SLOT(deleteLater()));

    // Connexion pour arreter l'application
    app->connect(e, SIGNAL(sig_finishedE()), SLOT(quit()));

    threadF->start();

    /*
      Affiche :
3070028656 void F::slot_startF() F::sig_F vers E::slot_E1
3071559376 void E::slot_E1() E::sig_E1 vers F::slot_F
3070028656 void F::slot_F() F::sig_finishedF vers E::slot_E2, F::deleteLater, QThread::quit
3071559376 void E::slot_E2() E::sig_finishedE vers E::deleteLater
3070028656 virtual F::~F()
3071559376 virtual E::~E()
      */
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    //test1(&app);
    //test2(&app);
    test3(&app);

    return app.exec();
}
