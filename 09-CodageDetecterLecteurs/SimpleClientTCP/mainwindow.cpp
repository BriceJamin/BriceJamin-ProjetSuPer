#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newClientPushButton_clicked()
{
    QString serverAddress = ui->serverAddressLineEdit->text();
    QString serverPort = ui->serverPortLineEdit->text();
    ClientTcpWindow* clientTcpWindow = new ClientTcpWindow(serverAddress, serverPort, this);
    clientTcpWindowList << clientTcpWindow;
    clientTcpWindow->setWindowFlags(Qt::Window);
    clientTcpWindow->show();
}
