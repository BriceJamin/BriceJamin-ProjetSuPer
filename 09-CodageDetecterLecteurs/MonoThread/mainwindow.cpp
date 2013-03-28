#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Server* server, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _server = server;
    ui->addressLineEdit->setText(server->address());
    ui->portSpinBox->setValue(server->port());

    connect(ui->onPushButton, SIGNAL(clicked()), _server, SLOT(slot_switchOn()));
    connect(ui->offPushButton, SIGNAL(clicked()), _server, SLOT(slot_switchOff()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
