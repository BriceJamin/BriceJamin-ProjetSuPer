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

QString Person::name() const
{
    return _name;
}

QString Person::firstname() const
{
    return _firstname;
}

QString Person::company() const
{
    return _company;
}

QDate Person::startDate() const
{
    return _startDate;
}

QDate Person::endDate() const
{
    return _endDate;
}

QDir Person::photo() const
{
    return _photo;
}

/*bool Person::isEmpty()
{
    return _name.isEmpty() | _firstname.isEmpty();
}*/
