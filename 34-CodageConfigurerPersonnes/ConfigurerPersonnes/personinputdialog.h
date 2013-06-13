#ifndef PERSONINPUTDIALOG_H
#define PERSONINPUTDIALOG_H

#include <QDialog>


class PersonInputDialog : public QDialog
{
    Q_OBJECT
    
public:
    PersonInputDialog(QWidget *parent = 0);
    ~PersonInputDialog();
    
private:
    QLineEdit* name;
    QLineEdit* firstname;

};

#endif // PERSONINPUTDIALOG_H
