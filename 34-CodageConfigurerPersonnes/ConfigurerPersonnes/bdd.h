#ifndef BDD_H
#define BDD_H

#include <QList>
#include "person.h"
#include <QSqlDatabase>

#define BDD_HOST_NAME       "localhost"
#define BDD_DATABASE_NAME   "bdd_super"
#define BDD_USER_NAME       "user_super"
#define BDD_PASSWORD        "mdp_super"

class Bdd
{
public:
    Bdd();
    ~Bdd();

    bool isOpen();
    bool personList(QList <Person>&);
    bool addPerson(const Person&);
    bool setPerson(const Person&, const Person&);

private:
    static int _instanceCount;
    static QSqlDatabase* _database;
    static bool _isOpen;
};

#endif // BDD_H
