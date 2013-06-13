#include "personinputdialog.h"

PersonInputDialog::PersonInputDialog(QWidget *parent) :
    QDialog(parent)
{
    // Identity Group
    name = new QLineEdit;
    firstname = new QLineEdit;

    QFormLayout *identityLayout = new QFormLayout;
    identityLayout->addRow("&Name :", name);
    identityLayout->addRow("&Firstname :", firstname);

    QGroupBox *identityGroup = new QGroupBox("Identity");
    identityGroup->setLayout(identityLayout);
}

PersonInputDialog::~PersonInputDialog()
{
}
