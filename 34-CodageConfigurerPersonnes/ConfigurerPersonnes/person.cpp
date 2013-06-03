#include "person.h"

void Person::setName(QString name)
{
    _name = name;
}

void Person::setFirstname(QString firstname)
{
    _firstname = firstname;
}

void Person::setCompany(QString company)
{
    _company = company;
}

void Person::setStartDate(QDate startDate)
{
    _startDate = startDate;
}

void Person::setEndDate(QDate endDate)
{
    _endDate = endDate;
}

void Person::setPhoto(QDir photo)
{
    _photo = photo;
}

QString Person::name()
{
    return _name;
}

QString Person::firstname()
{
    return _firstname;
}

QString Person::company()
{
    return _company;
}

QDate Person::startDate()
{
    return _startDate;
}

QDate Person::endDate()
{
    return _endDate;
}

QDir Person::photo()
{
    return _photo;
}

/*bool Person::isEmpty()
{
    return _name.isEmpty() | _firstname.isEmpty();
}*/
