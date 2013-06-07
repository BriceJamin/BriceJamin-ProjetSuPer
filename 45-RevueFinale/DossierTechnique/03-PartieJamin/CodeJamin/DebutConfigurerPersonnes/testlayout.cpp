#include "testlayout.h"
#include "ui_testlayout.h"

TestLayout::TestLayout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestLayout)
{
    ui->setupUi(this);
}

TestLayout::~TestLayout()
{
    delete ui;
}

void TestLayout::changeEvent(QEvent *e)
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
