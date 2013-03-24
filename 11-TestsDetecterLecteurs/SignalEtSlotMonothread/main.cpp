#include <QtCore>
#include "a.h"
#include "b.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    A a; B b;

    // Sans option, c'est l'option Qt::AutoConnection par défaut
    //  qui est équivalent à Qt::DirectConnection si les deux objets sont dans le même thread
    //  qui est équivalent à Qt::QueuedConnection si les deux objets sont dans des threads différents
    // Ici les objets sont dans le même thread : Qt::DirectConnection
    // Ce qui revient à faire un appel direct au slot de B (comme
    //  un appel normal à une méthode normale)
    /* Affiche :
        void A::start()
        Avant emit sig_A()
        void B::slot_B()
        Apres emit sig_A() et avant boucle infinie
    */
    // b.connect(&a, SIGNAL(sig_A()), SLOT(slot_B()));

    /* Affiche la même chose que précédement :
        void A::start()
        Avant emit sig_A()
        void B::slot_B()
        Apres emit sig_A() et avant boucle infinie
    */
    // b.connect(&a, SIGNAL(sig_A()), SLOT(slot_B()), Qt::DirectConnection);

    // Avec l'option Qt::QueuedConnection le signal est empilé
    //  dans la boucle d'évenement et le slot est exécuté dans le thread
    //  de l'objet recepteur une fois que (???)
    // Ici les deux objets sont dans le même threads, donc la boucle infinie
    //  a
    //    - un effet bloquant sur le thread du récepteur
    //    - peut être un effet bloquant sur l'event loop  (à tester)
    // Le thread du recepteur n'est pas libre, le slot ne s'exécute
    //  donc pas.
    /* Affiche :
        void A::start()
        Avant emit sig_A()
        Apres emit sig_A() et avant boucle infinie
    */
    b.connect(&a, SIGNAL(sig_A()), SLOT(slot_B()), Qt::QueuedConnection);

    app.connect(&a, SIGNAL(sig_A()), SLOT(quit()));

    a.start();

    return app.exec();
}
