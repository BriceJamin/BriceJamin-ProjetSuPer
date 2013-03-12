#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    clientTcpWindow(0)
{
    ui->setupUi(this);
    clientTcpWindow = new clientTcpWindow(this);

    ui->clientAddressLineEdit->setText(clientTcpWindow->getPeerAddress());

    connect(clientTcpWindow, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(clientTcpWindow_error(QAbstractSocket::SocketError)));
    connect(clientTcpWindow, SIGNAL(connected()), this, SLOT(clientTcpWindow_connected()));
    connect(clientTcpWindow, SIGNAL(disconnected()), this, SLOT(clientTcpWindow_disconnected()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectPushButton_clicked()
{
    ui->connectPushButton->setEnabled(false);
    clientTcpWindow->abort();
    clientTcpWindow->setPeerAddress(ui->clientAddressLineEdit->text());
    clientTcpWindow->connectToHost(ui->serverAddressLineEdit->text(), ui->serverPortLineEdit->text().toInt());
}


void MainWindow::clientTcpWindow_connected()
{
    ui->plainTextEdit->appendPlainText("***** Connected.");
}

void MainWindow::clientTcpWindow_disconnected()
{
    ui->plainTextEdit->appendPlainText("***** Disconnected.");
}

void MainWindow::clientTcpWindow_error(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        ui->plainTextEdit->appendPlainText("***** Host not found.");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        ui->plainTextEdit->appendPlainText("***** Connection refused.");
        break;
    default:
        ui->plainTextEdit->appendPlainText("***** Error occurred: " + clientTcpWindow->errorString());
    }
    ui->connectPushButton->setEnabled(true);
}
