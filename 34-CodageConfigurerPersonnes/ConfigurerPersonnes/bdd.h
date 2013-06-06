#ifndef BDD_H
#define BDD_H

#include <QList>
#include "person.h"
#include <QSqlDatabase>

class Bdd
{
public:
    Bdd();
    bool listPersons(QList <Person>&);
    bool addPerson(const Person&);
    bool setPerson(const Person&, const Person&);

private:
    QSqlDatabase _database;
};

#endif // BDD_H
