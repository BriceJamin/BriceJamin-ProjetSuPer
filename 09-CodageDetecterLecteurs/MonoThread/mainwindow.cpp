#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

MainWindow::MainWindow(Server* server, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << server << parent;

    ui->setupUi(this);
    _server = server;

    ui->addressLineEdit->setText(server->address());
    ui->portSpinBox->setValue(server->port());

    connect(ui->onPushButton, SIGNAL(clicked()), this, SLOT(onPushButton_clicked()));
    connect(ui->offPushButton, SIGNAL(clicked()), _server, SLOT(switchOff()));

    connect(ui->addressLineEdit, SIGNAL(textChanged(QString)), this, SLOT(addressLineEdit_textEdited(QString)));
    connect(ui->portSpinBox, SIGNAL(valueChanged(QString)), _server, SLOT(setPort(QString)));

    connect(server, SIGNAL(sig_switchedOn()), this, SLOT(server_switchedOn()));
    connect(server, SIGNAL(sig_switchedOff()), this, SLOT(server_switchedOff()));

    connect(server, SIGNAL(sig_addressChanged(QString)), this, SLOT(server_addressChanged(QString)));
    connect(server, SIGNAL(sig_portChanged(quint16)), this, SLOT(server_portChanged(quint16)));
}

MainWindow::~MainWindow()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;

    delete ui;
}

void MainWindow::addressLineEdit_textEdited(QString textEdited)
{
    QString color;
    bool ok;

    ok = _server->setAddress(textEdited);

    if(ok)
        color = "green";
    else
        color = "red";

    ui->addressLineEdit->setStyleSheet("color:" + color);

    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << textEdited << "-> " + color;
}

void MainWindow::onPushButton_clicked()
{
    QString errorColor = "red";
    Server::SwitchOnState state;

    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;

    state = _server->switchOn();

    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "switchOn() :" << state;

    switch(state)
    {
    case Server::Success:
        ui->addressLineEdit->setStyleSheet("");
        ui->portSpinBox->setStyleSheet("");
        break;

    case Server::AddressNotAvailableError:
        ui->addressLineEdit->setStyleSheet("background-color:" + errorColor);
        break;

    case Server::PortProtectedError:
    case Server::PortAlreadyInUseError:
        ui->portSpinBox->setStyleSheet("background-color:" + errorColor);
        break;

    default:
        ;
    }
}

void MainWindow::server_switchedOn()
{
    ui->onPushButton->setStyleSheet("background-color:green");
    ui->onPushButton->setEnabled(false);

    ui->offPushButton->setStyleSheet("");
    ui->offPushButton->setEnabled(true);

    ui->addressLineEdit->setEnabled(false);
    ui->portSpinBox->setEnabled(false);

    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "design";
}

void MainWindow::server_switchedOff()
{
    ui->offPushButton->setStyleSheet("background-color:red");
    ui->offPushButton->setEnabled(false);

    ui->onPushButton->setStyleSheet("");
    ui->onPushButton->setEnabled(true);

    ui->addressLineEdit->setEnabled(true);
    ui->portSpinBox->setEnabled(true);

    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << "design";
}

void MainWindow::server_addressChanged(QString address)
{
    QString text = ui->addressLineEdit->text();

    if(text != address)
    {
        qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << address << "setText addressLineEdit";

        ui->addressLineEdit->setText(address);
    }
}

void MainWindow::server_portChanged(quint16 port)
{
    quint16 value = ui->portSpinBox->value();

    if(value != port)
    {
        qDebug() << QThread::currentThreadId() << Q_FUNC_INFO << port << "setValue portSpinBox";

        ui->portSpinBox->setValue(port);
    }
}

void MainWindow::on_killAllComPushButton_clicked()
{
    qDebug() << QThread::currentThreadId() << Q_FUNC_INFO;
    _server->killAllCommunications();
}
