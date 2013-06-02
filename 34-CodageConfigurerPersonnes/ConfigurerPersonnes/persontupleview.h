#ifndef PERSONTUPLEVIEW_H
#define PERSONTUPLEVIEW_H

#include <QWidget>
#include <QDate>
#include <QDir>

namespace Ui {
    class PersonTupleView;
}

class PersonTupleView : public QWidget {
    Q_OBJECT
public:
    PersonTupleView(QWidget *parent = 0);
    ~PersonTupleView();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::PersonTupleView *ui;
    QDir _previousDir;

private slots:
    void on_finDateEdit_dateChanged(QDate date);
    void on_debutDateEdit_dateChanged(QDate date);
    void on_urlPhotoPushButton_clicked();
};

#endif // PERSONTUPLEVIEW_H
