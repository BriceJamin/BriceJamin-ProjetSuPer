#include "clienttcpwindow.h"
#include "ui_clienttcpwindow.h"

ClientTcpWindow::ClientTcpWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientTcpWindow)
{
    ui->setupUi(this);
}

ClientTcpWindow::~ClientTcpWindow()
{
    delete ui;
}
