#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    clientTcp(0)
{
    ui->setupUi(this);
    clientTcp = new ClientTcp(this);

    ui->clientAddressLineEdit->setText(clientTcp->getPeerAddress());

    connect(clientTcp, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(clientTcp_error(QAbstractSocket::SocketError)));
    connect(clientTcp, SIGNAL(connected()), this, SLOT(clientTcp_connected()));
    connect(clientTcp, SIGNAL(disconnected()), this, SLOT(clientTcp_disconnected()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectPushButton_clicked()
{
    ui->connectPushButton->setEnabled(false);
    clientTcp->abort();
    clientTcp->setPeerAddress(ui->clientAddressLineEdit->text());
    clientTcp->connectToHost(ui->serverAddressLineEdit->text(), ui->serverPortLineEdit->text().toInt());
}


void MainWindow::clientTcp_connected()
{
    ui->plainTextEdit->appendPlainText("***** Connected.");
}

void MainWindow::clientTcp_disconnected()
{
    ui->plainTextEdit->appendPlainText("***** Disconnected.");
}

void MainWindow::clientTcp_error(QAbstractSocket::SocketError socketError)
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
        ui->plainTextEdit->appendPlainText("***** Error occurred: " + clientTcp->errorString());
    }
    ui->connectPushButton->setEnabled(true);
}
