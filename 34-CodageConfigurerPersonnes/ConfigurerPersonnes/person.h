#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QDate>
#include <QMetaType>

class Person
{
public:
    Person();
    Person(const Person&);
    ~Person();

    bool setName(const QString&);
    bool setFirstname(const QString&);
    void setCompany(const QString&);
    void setInterventionPeriod(const QDate&, const QDate&);
    bool setPhoto(const QString&);

    QString name() const;
    bool nameIsValid() const;
    QString firstname() const;
    bool firstnameIsValid() const;
    QString company() const;
    QDate firstDayIntervention() const;
    QDate lastDayIntervention() const;
    void interventionPeriod(QDate&, QDate&) const;
    QString photo() const;
    bool isNull() const;
    bool isValid() const;

    Person& operator=(const Person&);

    static bool isAValidPhoto(const QString&);

private :
    QString _name;
    QString _firstname;
    QString _company;
    QDate _firstDayIntervention;
    QDate _lastDayIntervention;
    QString _photo;

    bool _nameIsValid;
    bool _firstnameIsValid;
    bool _identityIsValid;

    void refreshIdentity();
};

QDebug& operator<<(QDebug, const Person&);

Q_DECLARE_METATYPE(Person)

#endif // PERSON_H
