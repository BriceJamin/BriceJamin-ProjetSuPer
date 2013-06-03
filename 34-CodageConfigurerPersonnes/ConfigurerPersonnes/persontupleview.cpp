#include "persontupleview.h"
#include "ui_persontupleview.h"
#include <QFileDialog>
#include <QSize>
#include <QPixmap>

PersonTupleView::PersonTupleView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonTupleView)
{
    ui->setupUi(this);

    QDate todayDate = QDate::currentDate();
    ui->debutDateEdit->setDate(todayDate);
    ui->finDateEdit->setDate(todayDate);
}

PersonTupleView::~PersonTupleView()
{
    delete ui;
}

QString PersonTupleView::methodeTest()
{
    PersonTupleView personTupleView;
    personTupleView.show();

    return "It works ! =)";
}

void PersonTupleView::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void PersonTupleView::on_urlPhotoPushButton_clicked()
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
        ui->urlPhotoLineEdit->setText(fileName);

        QPixmap pixmap(fileName);

        //QSize size(20, 20);
        //Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio;
        //Qt::TransformationMode transformationMode = Qt::SmoothTransformation;
        //pixmap.scaled(size, aspectRatioMode, transformationMode);

        if(! pixmap.isNull())
        {
            ui->photoLabel->setPixmap(pixmap);
            ui->urlPhotoLineEdit->setStyleSheet("QLineEdit { color : black; }");
        }
        else
        {
            ui->photoLabel->setStyleSheet("QLabel { background-color : red; color : black; }");
            ui->photoLabel->setText("Image invalide.");
            ui->urlPhotoLineEdit->setStyleSheet("QLineEdit { color : red; }");
        }
    }
}

void PersonTupleView::on_debutDateEdit_dateChanged(QDate date)
{
    if(date > ui->finDateEdit->date())
        ui->finDateEdit->setDate(date);
}

void PersonTupleView::on_finDateEdit_dateChanged(QDate date)
{
    if(date < ui->debutDateEdit->date())
        ui->debutDateEdit->setDate(date);
}
