#include "clienttcpwindow.h"
#include "ui_clienttcpwindow.h"

ClientTcpWindow::ClientTcpWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientTcpWindow)
{
    ui->setupUi(this);

    clientTcp = new ClientTcp(this);
    ui->clientAddressLineEdit->setText(clientTcp->getPeerAddress());

    connect(clientTcp, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(clientTcp_error(QAbstractSocket::SocketError)));
    connect(clientTcp, SIGNAL(connected()), this, SLOT(clientTcp_connected()));
    connect(clientTcp, SIGNAL(disconnected()), this, SLOT(clientTcp_disconnected()));

}

ClientTcpWindow::~ClientTcpWindow()
{
    delete ui;
}

void ClientTcpWindow::changeEvent(QEvent *e)
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

void ClientTcpWindow::on_connectPushButton_clicked()
{
    ui->connectPushButton->setEnabled(false);
    clientTcp->abort();
    clientTcp->setPeerAddress(ui->clientAddressLineEdit->text());
    clientTcp->connectToHost(ui->serverAddressLineEdit->text(), ui->serverPortLineEdit->text().toInt());
}

void ClientTcpWindow::clientTcpWindow_connected()
{
    ui->plainTextEdit->appendPlainText("***** Connected.");
}

void ClientTcpWindow::clientTcpWindow_disconnected()
{
    ui->plainTextEdit->appendPlainText("***** Disconnected.");
}

void ClientTcpWindow::clientTcp_error(QAbstractSocket::SocketError socketError)
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
