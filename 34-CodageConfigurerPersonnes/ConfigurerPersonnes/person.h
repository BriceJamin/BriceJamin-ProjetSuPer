#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QDate>
#include <QDir>

class Person
{
public:
    void setName(QString);
    void setFirstname(QString);
    void setCompany(QString);
    void setStartDate(QDate);
    void setEndDate(QDate);
    void setPhoto(QDir);

    QString name() const;
    QString firstname() const;
    QString company() const;
    QDate startDate() const;
    QDate endDate() const;
    QDir photo() const;

    //bool isNull();

private :
    QString _name;
    QString _firstname;
    QString _company;
    QDate _startDate;
    QDate _endDate;
    QDir _photo;
};

#endif // PERSON_H
