#ifndef PERSONDIALOG_H
#define PERSONDIALOG_H

#include <QDialog>
#include <QDate>

#include "person.h"

namespace Ui {
    class PersonDialog;
}

class PersonDialog : public QDialog {
    Q_OBJECT
public:
    PersonDialog(QWidget *parent = 0);
    ~PersonDialog();

    Person person();

    static Person getNewPersonInput();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::PersonDialog *ui;
    static QDir _previousDir;

private slots:
    void on_photoPathPushButton_clicked();
    void on_endDateEdit_dateChanged(QDate date);
    void on_startDateEdit_dateChanged(QDate date);
    void on_buttonBox_accepted();
};

#endif // PERSONDIALOG_H
