#include "detecterlecteurs.h"
#include "ui_detecterlecteurs.h"
#include "readerdetector.h"

DetecterLecteurs::DetecterLecteurs(ReaderDetector* rd, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DetecterLecteurs),
    readerDetector(rd)
{
    ui->setupUi(this);

    connect(this, SIGNAL(sig_occuredSignal(QString)), this, SLOT(occuredSignal(QString)));
    connect(readerDetector, SIGNAL(sig_switchedOn()), this, SLOT(readerDetector_switchedOn()));
    connect(readerDetector, SIGNAL(sig_errorOccurred(QString)), this, SLOT(readerDetector_errorOccurred(QString)));
    connect(readerDetector, SIGNAL(sig_switchedOff()), this, SLOT(readerDetector_switchedOff()));
    connect(readerDetector, SIGNAL(sig_clientDetected()), this, SLOT(readerDetector_clientDetected()));
    connect(readerDetector, SIGNAL(sig_intruderDetected()), this, SLOT(readerDetector_intruderDetected()));
    connect(readerDetector, SIGNAL(sig_readerDetected()), this, SLOT(readerDetector_readerDetected()));
}

DetecterLecteurs::~DetecterLecteurs()
{
    delete ui;
}

void DetecterLecteurs::readerDetector_switchedOn()
{
    emit sig_occuredSignal("readerDetector_switchedOn");
}

void DetecterLecteurs::readerDetector_errorOccurred(QString error)
{
    emit sig_occuredSignal("readerDetector_errorOccurred");
}


void DetecterLecteurs::readerDetector_switchedOff()
{
    emit sig_occuredSignal("readerDetector_switchedOff");
}


void DetecterLecteurs::readerDetector_clientDetected()
{
    emit sig_occuredSignal("readerDetector_clientDetected");
}


void DetecterLecteurs::readerDetector_intruderDetected()
{
    emit sig_occuredSignal("readerDetector_intruderDetected");
}


void DetecterLecteurs::readerDetector_readerDetected()
{
    emit sig_occuredSignal("readerDetector_readerDetected");
}


void DetecterLecteurs::readerDetector_destroyed()
{
    emit sig_occuredSignal("readerDetector_destroyed");
}



void DetecterLecteurs::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DetecterLecteurs::on_onPushButton_clicked()
{
    // Switch on readerDetector
    QString address = DetecterLecteurs::ui->addressLineEdit->text();
    unsigned int port = DetecterLecteurs::ui->portSpinBox->value();
    readerDetector->switchOn(address, port);
}

void DetecterLecteurs::on_offPushButton_clicked()
{
    // Switch off readerDetector
    readerDetector->switchOff();
}

void DetecterLecteurs::occuredSignal(QString signal)
{
    DetecterLecteurs::ui->messagesPlainTextEdit->appendPlainText(signal);
}
