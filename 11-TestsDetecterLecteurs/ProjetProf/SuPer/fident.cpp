#include "fident.h"
#include "ui_fident.h"

FIdent::FIdent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FIdent)
{
    ui->setupUi(this);
}

FIdent::~FIdent()
{
    delete ui;
}

void FIdent::on_buttonBox_rejected()
{
    close();
}

void FIdent::on_buttonBox_accepted()
{
    ihm = new MainWindow();
    ihm->show();
    close();
}
