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

    QString name();
    QString firstname();
    QString company();
    QDate startDate();
    QDate endDate();
    QDir photo();

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
