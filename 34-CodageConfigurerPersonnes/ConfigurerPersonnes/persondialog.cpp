#include "persondialog.h"
#include "ui_persondialog.h"

#include <QFileDialog>

QDir PersonDialog::_previousDir;

PersonDialog::PersonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonDialog)
{
    ui->setupUi(this);

    QDate currentDate = QDate::currentDate();
    ui->startDateEdit->setDate(currentDate);
    ui->endDateEdit->setDate(currentDate);
}

PersonDialog::~PersonDialog()
{
    delete ui;
}

void PersonDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

Person PersonDialog::person()
{
    Person person;

    person.setName(ui->nameLineEdit->text());
    person.setFirstname(ui->firstnameLineEdit->text());
    person.setCompany(ui->companyLineEdit->text());
    person.setStartDate(ui->startDateEdit->date());
    person.setEndDate(ui->endDateEdit->date());
    person.setPhoto(ui->photoPathLineEdit->text());

    return person;
}

Person PersonDialog::getNewPersonInput()
{
    PersonDialog dialog;

    if (dialog.exec() == QDialog::Accepted)
        return dialog.person();

    return Person();
}

void PersonDialog::on_buttonBox_accepted()
{

}

void PersonDialog::on_startDateEdit_dateChanged(QDate date)
{
    if(date > ui->endDateEdit->date())
        ui->endDateEdit->setDate(date);
}

void PersonDialog::on_endDateEdit_dateChanged(QDate date)
{
    if(date < ui->startDateEdit->date())
        ui->startDateEdit->setDate(date);
}

void PersonDialog::on_photoPathPushButton_clicked()
{
    QString readWritePixmapExtension = "*.bmp *.jpg *.jpeg *.png *.ppm *.xbm *.xpm";
    QString readOnlyPixmapExtension = "*.gif *.pbm *.pgm";

    QString caption = "Choisir une photo (120 x 120)";
    QString dir = _previousDir.path();
    QString filters;
    filters = "Images accepted (" + readWritePixmapExtension + readOnlyPixmapExtension + ")";
    filters += ";; Images read/write only (" + readWritePixmapExtension + ")";
    filters += ";; Images read only (" + readOnlyPixmapExtension + ")";

    QString fileName = QFileDialog::getOpenFileName(this, caption, dir, filters);

    if(! fileName.isEmpty())
    {
        _previousDir.setPath(fileName);
        ui->photoPathLineEdit->setText(fileName);

        QPixmap pixmap(fileName);

        if(! pixmap.isNull())
        {
            ui->photoLabel->setPixmap(pixmap);
            ui->photoPathLineEdit->setStyleSheet("QLineEdit { color : black; }");
        }
        else
        {
            ui->photoLabel->setStyleSheet("QLabel { background-color : red; color : black; }");
            ui->photoLabel->setText("Image invalide.");
            ui->photoPathLineEdit->setStyleSheet("QLineEdit { color : red; }");
        }
    }
}
