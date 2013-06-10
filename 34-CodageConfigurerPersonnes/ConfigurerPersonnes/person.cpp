#include <QFile>
#include <QPixmap>
#include <QDebug>
#include "person.h"

Person::Person() :
    _nameIsValid(false),
    _firstnameIsValid(false),
    _identityIsValid(false)
{
}

Person::Person(const Person& p) :
        _name(p._name),
        _firstname(p._firstname),
        _company(p._company),
        _firstDayIntervention(p._firstDayIntervention),
        _lastDayIntervention(p._lastDayIntervention),
        _photo(p._photo),
        _nameIsValid(p._nameIsValid),
        _firstnameIsValid(p._firstnameIsValid),
        _identityIsValid(p._identityIsValid)
{
}

Person::~Person()
{
}

bool Person::setName(const QString& name)
{
    if(name.isEmpty())
        return false;

    _name = name;
    _nameIsValid = true;

    refreshIdentity();

    return _nameIsValid;
}

bool Person::setFirstname(const QString& firstname)
{
    if(firstname.isEmpty())
        return false;

    _firstname = firstname;
    _firstnameIsValid = true;

    refreshIdentity();

    return _firstnameIsValid;
}

void Person::setCompany(const QString& company)
{
    _company = company;
}

void Person::setInterventionPeriod(const QDate& firstDay, const QDate& lastDay)
{
    _firstDayIntervention = firstDay;
    _lastDayIntervention = lastDay;

    if(firstDay.isValid() && lastDay.isValid()
        && (firstDay > lastDay))
    {
        _firstDayIntervention = lastDay;
        _lastDayIntervention = firstDay;
    }
}

bool Person::setPhoto(const QString& photo)
{
    if(! isAValidPhoto(photo))
        return false;

    _photo = photo;

    return true;
}

QString Person::name() const
{
    return _name;
}

bool Person::nameIsValid() const
{
    return _nameIsValid;
}

QString Person::firstname() const
{
    return _firstname;
}

bool Person::firstnameIsValid() const
{
    return _firstnameIsValid;
}

QString Person::company() const
{
    return _company;
}

QDate Person::firstDayIntervention() const
{
    return _firstDayIntervention;
}

QDate Person::lastDayIntervention() const
{
    return _lastDayIntervention;
}

void Person::interventionPeriod(QDate& firstDay, QDate& lastDay) const
{
    firstDay = _firstDayIntervention;
    lastDay = _lastDayIntervention;
}

QString Person::photo() const
{
    return _photo;
}

bool Person::isNull() const
{
    bool isNull = true;

    isNull &= _name.isNull();
    isNull &= _firstname.isNull();
    isNull &= _company.isNull();
    isNull &= _firstDayIntervention.isNull();
    isNull &= _lastDayIntervention.isNull();
    isNull &= _photo.isNull();

    return isNull;
}

bool Person::isValid() const
{
    return _identityIsValid;
}

Person& Person::operator=(const Person& other)
{
    _name = other._name;
    _firstname = other._firstname;
    _company = other._company;
    _firstDayIntervention = other._firstDayIntervention;
    _lastDayIntervention = other._lastDayIntervention;
    _photo = other._photo;
    _nameIsValid = other._nameIsValid;
    _firstnameIsValid = other._firstnameIsValid;
    _identityIsValid = other._identityIsValid;

    return *this;
}

bool Person::isAValidPhoto(const QString& photo)
{
    QFile photoFile(photo);

    if(! photoFile.exists())
        return false;

    QPixmap photoPixmap(photoFile.fileName());

    if(photoPixmap.isNull())
        return false;

    return true;
}

void Person::refreshIdentity()
{
    _identityIsValid = _nameIsValid && _firstnameIsValid;
}

QDebug& operator<<(QDebug debug, const Person& person)
{
    if(person.isNull())
        return debug.nospace() << "Person(\"\")";

    QString dateFormat = "YYYY-MM-DD";
    QString firstDayString, lastDayString;
    firstDayString = person.firstDayIntervention().toString(dateFormat);
    lastDayString = person.lastDayIntervention().toString(dateFormat);

    debug.nospace() << "Person(";
    debug.nospace() << person.name() << ",";
    debug.nospace() << person.firstname() << ",";
    debug.nospace() << person.company() << ",";
    debug.nospace() << firstDayString << ",";
    debug.nospace() << firstDayString << ",";
    debug.nospace() << person.photo() << ")";

    return debug.nospace();
}
