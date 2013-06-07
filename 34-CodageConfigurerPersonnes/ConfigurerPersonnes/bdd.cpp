#include "bdd.h"
#include <QSqlQuery>
#include <QDebug>

int Bdd::_instanceCount = 0;
QSqlDatabase* Bdd::_database = 0;
bool Bdd::_isOpen = false;

Bdd::Bdd()
{
    if(0 == _instanceCount)
    {
        _database = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
        _database->setHostName(BDD_HOST_NAME);
        _database->setDatabaseName(BDD_DATABASE_NAME);
        _database->setUserName(BDD_USER_NAME);
        _database->setPassword(BDD_PASSWORD);

        if(_database->open())
            _isOpen = true;
        else
            _isOpen = false;
    }

    _instanceCount++;
}

Bdd::~Bdd()
{
    _instanceCount--;

    if(0 == _instanceCount)
            delete _database;
}

bool Bdd::isOpen()
{
    return _isOpen;
}

bool Bdd::personList(QList <Person>&)
{
    return true;
}

bool Bdd::addPerson(const Person& person)
{
    qDebug() << Q_FUNC_INFO << "addPerson : _isOpen" << _isOpen;
    if(! _isOpen)
        return false;

    QString queryString;
    queryString += "INSERT INTO personne ";
    queryString += "(nom, prenom, societe, dateDebut, dateFin, photo) ";
    queryString += "VALUES (";
    queryString += "'" + person.name() + "', ";
    queryString += "'" + person.firstname() + "', ";
    queryString += "'" + person.company() + "', ";
    queryString += "'" + person.startDate().toString(Qt::ISODate) + "',";
    queryString += "'" + person.endDate().toString(Qt::ISODate) + "',";
    queryString += "'" + person.photo().path() + "'";
    queryString += ");";
    qDebug() << queryString;

    QSqlQuery query(*_database);
    query.exec(queryString);

    return query.isActive();
}

bool Bdd::setPerson(const Person&, const Person&)
{
    return true;
}
