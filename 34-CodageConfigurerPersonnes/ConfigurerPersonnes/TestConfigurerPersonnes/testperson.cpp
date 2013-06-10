// 80,87s/^\(\s*\).*<\(.*\)>("\(.*\)"/\1QFETCH(\2 \3/g
#include "testperson.h"
#include "../person.h"

void TestPerson::setName_data()
{
    QString null, empty(""), name("Jamin");
    QCOMPARE(null.isNull(), true);
    QCOMPARE(empty.isEmpty() && !empty.isNull(), true);
    QCOMPARE(name, QString("Jamin"));

    QTest::addColumn<Person>("person");
    QTest::addColumn<QString>("nameSetter");
    QTest::addColumn<bool>("returnExpected");
    QTest::addColumn<QString>("nameExpected");
    QTest::addColumn<bool>("isValidExpected");

    Person person;
    QTest::newRow("null_1")  << person << null  << false << null << false;
    QTest::newRow("empty_1") << person << empty << false << null << false;
    QTest::newRow("valid_1") << person << name  << true  << name << true;

    person.setName(name);
    QTest::newRow("null_2")  << person << null  << false << name << true;
    QTest::newRow("empty_2") << person << empty << false << name << true;

    name = "Scherer";
    QTest::newRow("valid_2") << person << name  << true  << name << true;
}

void TestPerson::setName()
{
    QFETCH(Person, person);
    QFETCH(QString, nameSetter);
    QFETCH(bool, returnExpected);
    QFETCH(QString, nameExpected);
    QFETCH(bool, isValidExpected);

    bool returnActual = person.setName(nameSetter);
    QString nameActual = person.name();
    bool isValidActual = person.nameIsValid();

    QCOMPARE(returnActual, returnExpected);
    QCOMPARE(nameActual, nameExpected);
    QCOMPARE(isValidActual, isValidExpected);
}

void TestPerson::setFirstname_data()
{
    QString null, empty(""), valid("Brice");
    QCOMPARE(null.isNull(), true);
    QCOMPARE(empty.isEmpty() && !empty.isNull(), true);

    QTest::addColumn<Person>("person");
    QTest::addColumn<QString>("firstnameSetter");
    QTest::addColumn<bool>("returnExpected");
    QTest::addColumn<QString>("firstnameExpected");
    QTest::addColumn<bool>("isValidExpected");

    Person person;
    QTest::newRow("null_1")  << person << null  << false << null << false;
    QTest::newRow("empty_1") << person << empty << false << null << false;
    QTest::newRow("valid_1") << person << valid  << true  << valid << true;

    person.setFirstname(valid);
    QTest::newRow("null_2")  << person << null  << false << valid << true;
    QTest::newRow("empty_2") << person << empty << false << valid << true;

    valid = "Nicolas";
    QTest::newRow("valid_2") << person << valid  << true  << valid << true;
}

void TestPerson::setFirstname()
{
    QFETCH(Person, person);
    QFETCH(QString, firstnameSetter);
    QFETCH(bool, returnExpected);
    QFETCH(QString, firstnameExpected);
    QFETCH(bool, isValidExpected);

    bool returnActual = person.setFirstname(firstnameSetter);
    QString firstnameActual = person.firstname();
    bool isValidActual = person.firstnameIsValid();

    QCOMPARE(returnActual, returnExpected);
    QCOMPARE(firstnameActual, firstnameExpected);
    QCOMPARE(isValidActual, isValidExpected);
}

void TestPerson::setCompany()
{
    Person person;
    QString expected("Company");
    person.setCompany(expected);
    QCOMPARE(person.company(), expected);
}

void TestPerson::setInterventionPeriod_data()
{
    Person person;
    QDate null;
    QDate first(2004,4,4);
    QDate middle(2005,5,5);
    QDate last(2006,6,6);

    QCOMPARE(null.isNull(), true);
    QCOMPARE(first < middle, true);
    QCOMPARE(middle < last, true);

    QTest::addColumn<QDate>("date1");
    QTest::addColumn<QDate>("date2");
    QTest::addColumn<QDate>("expected1");
    QTest::addColumn<QDate>("expected2");

    QTest::newRow("1 = 2") << middle << middle << middle << middle;
    QTest::newRow("1 < 2") << first << last << first << last;
    QTest::newRow("1 > 2") << last << first << first << last;
    QTest::newRow("null, 2") << null << middle << null << middle;
    QTest::newRow("1, null") << middle << null << middle << null;
    QTest::newRow("null, null") << null << null << null << null;
}

void TestPerson::setInterventionPeriod()
{
    Person person;
    QDate actual1;
    QDate actual2;

    QFETCH(QDate, date1);
    QFETCH(QDate, date2);
    QFETCH(QDate, expected1);
    QFETCH(QDate, expected2);

    person.setInterventionPeriod(date1, date2);
    person.interventionPeriod(actual1, actual2);

    QCOMPARE(actual1, expected1);
    QCOMPARE(actual2, expected2);
}

void TestPerson::setPhoto_data()
{
    QTest::addColumn<QString>("photo");
    QTest::addColumn<bool>("returnExpected");
    QTest::addColumn<QString>("photoExpected");

    QTest::newRow("invalid path") << "lkj(*:qp&" << false << QString();
    QTest::newRow("text file") << "Images/file.txt" << false << QString();
    QTest::newRow("invalid jpeg file") << "Images/inconnu.jpg" << false << QString();
    QTest::newRow("valid") << "Images/moi.jpg" << true << "Images/moi.jpg";
}

void TestPerson::setPhoto()
{
    QFETCH(QString, photo);
    QFETCH(bool, returnExpected);
    QFETCH(QString, photoExpected);

    Person person;
    bool returnActual = person.setPhoto(photo);
    QString photoActual = person.photo();

    QCOMPARE(returnActual, returnExpected);
    QCOMPARE(photoActual, photoExpected);
}

void TestPerson::name()
{
    Person person;
    QString name("Jamin");
    QCOMPARE(person.name(), QString());
    person.setName(name);
    QCOMPARE(person.name(), name);
}

void TestPerson::nameIsValid()
{
    Person person;
    QCOMPARE(person.nameIsValid(), false);
    person.setName("Jamin");
    QCOMPARE(person.nameIsValid(), true);
}

void TestPerson::firstname()
{
    Person person;
    QString firstname("Brice");
    QCOMPARE(person.firstname(), QString());
    person.setFirstname(firstname);
    QCOMPARE(person.firstname(), firstname);
}

void TestPerson::firstnameIsValid()
{
    Person person;
    QCOMPARE(person.firstnameIsValid(), false);
    person.setFirstname("Brice");
    QCOMPARE(person.firstnameIsValid(), true);
}

void TestPerson::company()
{
    Person person;
    QString company("Company");
    QCOMPARE(person.company(), QString());
    person.setCompany(company);
    QCOMPARE(person.company(), company);
}

void TestPerson::firstDayIntervention()
{
    Person person;
    QDate day1(2001,1,1), day2(2002,2,2);
    QCOMPARE(person.firstDayIntervention(), QDate());
    person.setInterventionPeriod(day1, day2);
    QCOMPARE(person.firstDayIntervention(), day1);
}

void TestPerson::lastDayIntervention()
{
    Person person;
    QDate day1(2001,1,1), day2(2002,2,2);
    QCOMPARE(person.lastDayIntervention(), QDate());
    person.setInterventionPeriod(day1, day2);
    QCOMPARE(person.lastDayIntervention(), day2);
}

void TestPerson::interventionPeriod()
{
    Person person;
    QDate day1(2001,1,1), day2(2002,2,2);
    person.interventionPeriod(day1, day2);
    QCOMPARE(person.firstDayIntervention(), day1);
    QCOMPARE(person.lastDayIntervention(), day2);
}

void TestPerson::photo()
{
    Person person;
    QString photo("Images/moi.jpg");
    person.setPhoto(photo);
    QCOMPARE(person.photo(), photo);
}

void TestPerson::isNull_data()
{
    QTest::addColumn<Person>("person");
    QTest::addColumn<bool>("returnExpected");

    Person isNull;
    Person name; name.setName("Jamin");
    Person firstname; firstname.setFirstname("Brice");
    Person company; company.setCompany("Company");
    QDate null, first(20005,5,5), last(2006,6,6);
    Person firstDay; firstDay.setInterventionPeriod(first, null);
    Person lastDay; lastDay.setInterventionPeriod(null, last);
    Person photo; photo.setPhoto("Images/moi.jpg");

    QTest::newRow("is null") << isNull << true;
    QTest::newRow("!name") << name << false;
    QTest::newRow("!firstname") << firstname << false;
    QTest::newRow("!company") << company << false;
    QTest::newRow("!firstDay") << firstDay << false;
    QTest::newRow("!lastDay") << lastDay << false;
    QTest::newRow("!photo") << photo << false;
}

void TestPerson::isNull()
{
    QFETCH(Person, person);
    QFETCH(bool, returnExpected);

    bool returnActual = person.isNull();
    QCOMPARE(returnActual, returnExpected);
}

void TestPerson::operatorEqual()
{
    Person null;
    Person full;
    QString name("Jamin");
    QString firstname("Brice");
    QString company("Company");
    QDate first(2001,1,1);
    QDate last(2002,2,2);
    QString photo("Images/moi.jpg");

    full.setName(name);
    full.setFirstname(firstname);
    full.setCompany(company);
    full.setInterventionPeriod(first, last);
    full.setPhoto(photo);

    null = full;

    QCOMPARE(null.name(), full.name());
    QCOMPARE(null.firstname(), full.firstname());
    QCOMPARE(null.company(), full.company());
    QCOMPARE(null.firstDayIntervention(), full.firstDayIntervention());
    QCOMPARE(null.lastDayIntervention(), full.lastDayIntervention());
    QCOMPARE(null.photo(), full.photo());
    QCOMPARE(null.nameIsValid(), full.nameIsValid());
    QCOMPARE(null.firstnameIsValid(), full.firstnameIsValid());
    QCOMPARE(null.isNull(), full.isNull());
    QCOMPARE(null.isValid(), full.isValid());
}

void TestPerson::isAValidPhoto_data()
{
    QTest::addColumn<QString>("photo");
    QTest::addColumn<bool>("returnExpected");

    QTest::newRow("invalid path") << "lkj(*:qp&" << false;
    QTest::newRow("text file") << "Images/file.txt" << false;
    QTest::newRow("invalid jpeg file") << "Images/inconnu.jpg" << false;
    QTest::newRow("valid") << "Images/moi.jpg" << true;
}

void TestPerson::isAValidPhoto()
{
    QFETCH(QString, photo);
    QFETCH(bool, returnExpected);

    bool returnActual = Person::isAValidPhoto(photo);

    QCOMPARE(returnActual, returnExpected);
}
