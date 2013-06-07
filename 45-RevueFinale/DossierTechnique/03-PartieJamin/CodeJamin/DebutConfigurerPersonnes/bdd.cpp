#include "bdd.h"

Bdd::Bdd() : _database(QSqlDatabase::addDatabase("QMYSQL"))
{

}

bool listPersons(QList <Person>&)
{
    return true;
}

bool addPerson(const Person&)
{
    return true;
}

bool setPerson(const Person&, const Person&)
{
    return true;
}
