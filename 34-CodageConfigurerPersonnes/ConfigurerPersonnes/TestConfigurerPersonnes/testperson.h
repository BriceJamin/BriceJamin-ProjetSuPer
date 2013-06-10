#ifndef TESTPERSON_H
#define TESTPERSON_H

#include <QtTest/QtTest>

class TestPerson : public QObject
{
    Q_OBJECT

private slots:

    void setName_data();
    void setName();
    void setFirstname_data();
    void setFirstname();
    void setCompany();
    void setInterventionPeriod_data();
    void setInterventionPeriod();
    void setPhoto_data();
    void setPhoto();
    void name();
    void nameIsValid();
    void firstname();
    void firstnameIsValid();
    void company();
    void firstDayIntervention();
    void lastDayIntervention();
    void interventionPeriod();
    void photo();
    void isNull_data();
    void isNull();
    void operatorEqual();
    void isAValidPhoto_data();
    void isAValidPhoto();
};

#endif // TESTPERSON_H
