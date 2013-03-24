#include <QtCore>
#include "parent.h"
#include "fils.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Parent* parent = new Parent();
    app.connect(parent, SIGNAL(destroyed()), SLOT(quit()));

    // Fils* fils = new Fils();
    // Aucun affichage : le destructeur de fils n'est pas appelé !

    Fils* fils = new Fils(parent);
    // S'affiche "virtual Fils::~Fils()"
    // Le destructeur de Fils est donc appelé !

    parent->deleteLater();
    return app.exec();
}
