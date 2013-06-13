#ifndef PERSONDIALOG_H
#define PERSONDIALOG_H

#include <QDialog>
#include <QDate>

#include "person.h"
#include "bdd.h"

namespace Ui {
    class PersonDialog;
}

class PersonDialog : public QDialog {
    Q_OBJECT
public:
    PersonDialog(QWidget *parent = 0);
    ~PersonDialog();

    Person person;

    static Person getNewPersonInput();

public slots:
    virtual void accept();


protected:
    void changeEvent(QEvent *e);

private:
    Ui::PersonDialog *ui;
    QFile _photoFile;
    static QDir _previousDir;
    //Bdd bdd;

private slots:
    void on_photoPathPushButton_clicked();
    void on_endDateEdit_dateChanged(QDate date);
    void on_startDateEdit_dateChanged(QDate date);
};

#endif // PERSONDIALOG_H
