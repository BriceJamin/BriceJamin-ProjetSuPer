#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readFortune()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectPushButton_clicked()
{
    ui->connectPushButton->setEnabled(false);
    tcpSocket->abort();
    tcpSocket->setPeerAddress(QHostAddress(ui->clientAddressLineEdit->text()));
    tcpSocket->connectToHost(ui->serverAddressLineEdit->text(), ui->serverPortLineEdit->text().toInt());
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
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
         ui->plainTextEdit->appendPlainText("***** Error occurred: " + tcpSocket->errorString());
     }
     ui->connectPushButton->setEnabled(true);
 }
