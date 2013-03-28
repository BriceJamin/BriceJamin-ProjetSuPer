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

    connect(ui->onPushButton, SIGNAL(clicked()), _server, SLOT(switchOn()));
    connect(ui->offPushButton, SIGNAL(clicked()), _server, SLOT(switchOff()));
    connect(ui->addressLineEdit, SIGNAL(textChanged(QString)), this, SLOT(addressLineEdit_textEdited(QString)));
    connect(ui->portSpinBox, SIGNAL(valueChanged(QString)), _server, SLOT(setPort(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addressLineEdit_textEdited(QString textEdited)
{
    QString color;

    if(_server->setAddress(textEdited))
        color = "green";
    else
        color = "red";

    ui->addressLineEdit->setStyleSheet("QLineEdit{color:" + color + ";}");

    qDebug() << Q_FUNC_INFO << textEdited << "-> " + color;
}
