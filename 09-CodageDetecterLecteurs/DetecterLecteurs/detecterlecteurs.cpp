#include "detecterlecteurs.h"
#include "ui_detecterlecteurs.h"
#include "readerdetector.h"

DetecterLecteurs::DetecterLecteurs(ReaderDetector* rd, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DetecterLecteurs),
    readerDetector(rd)
{
    ui->setupUi(this);

    // this' signals to this' slots connection
    connect(this, SIGNAL(sig_occuredSignal(QString)), this, SLOT(occuredSignal(QString)));

    // this' signals to ReaderDetector's slots connection
    connect(this, SIGNAL(sig_switchOn_readerDetector(QString, unsigned int)), readerDetector, SLOT(switchOn(QString, unsigned int)));
    connect(this, SIGNAL(sig_switchOff_readerDetector()), readerDetector, SLOT(switchOff()));

    // ReaderDetector's signals to this' slots connection
    connect(readerDetector, SIGNAL(sig_switchedOn()), this, SLOT(readerDetector_switchedOn()));
    connect(readerDetector, SIGNAL(sig_errorOccurred(QString)), this, SLOT(readerDetector_errorOccurred(QString)));
    connect(readerDetector, SIGNAL(sig_switchedOff()), this, SLOT(readerDetector_switchedOff()));
    connect(readerDetector, SIGNAL(sig_intruderEjected(QString)), this, SLOT(readerDetector_intruderEjected(QString)));
    connect(readerDetector, SIGNAL(sig_readerConnected(Reader*)), this, SLOT(readerDetector_readerConnected(Reader*)));
    connect(readerDetector, SIGNAL(sig_readerDisconnected(Reader*)), this, SLOT(readerDetector_readerDisconnected(Reader*)));
    connect(readerDetector, SIGNAL(destroyed()), this, SLOT(readerDetector_destroyed()));
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
    emit sig_occuredSignal("readerDetector_errorOccurred :" + error);
}


void DetecterLecteurs::readerDetector_switchedOff()
{
    emit sig_occuredSignal("readerDetector_switchedOff");
}

void DetecterLecteurs::readerDetector_intruderEjected(QString address)
{
    emit sig_occuredSignal("readerDetector_intruderDetected : " + address);
}


void DetecterLecteurs::readerDetector_readerConnected(Reader* reader)
{
    QString msg;
    msg += "Reader : ";
    msg += "Num(" + QString::number(reader->number()) + "), ";
    msg += "PlaceId(" + QString::number(reader->placeId()) + "), ";
    msg += "Address(" + reader->address() + "), ";
    msg += "IsConnected(" + QString::number(reader->isConnected()) + ").";
    emit sig_occuredSignal("readerDetector_readerDetected :" + msg);
    //connect(reader, SIGNAL(sig_disconnected()), this, SLOT()
}

void DetecterLecteurs::readerDetector_readerDisconnected(Reader* reader)
{
    QString msg;
    msg += "Reader : ";
    msg += "Num(" + QString::number(reader->number()) + "), ";
    msg += "PlaceId(" + QString::number(reader->placeId()) + "), ";
    msg += "Address(" + reader->address() + "), ";
    msg += "IsConnected(" + QString::number(reader->isConnected()) + ").";
    emit sig_occuredSignal("readerDetector_readerDisconnected :" + msg);
}

void DetecterLecteurs::readerDetector_destroyed()
{
    /*qulonglong readerDetectorQll = (qulonglong) readerDetector;
    QString readerDetectorString = QString("0x%1").arg(readerDetectorQll, 8, '0');
    emit sig_occuredSignal("readerDetector_destroyed, readerDetector :" + readerDetectorString);*/
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

void DetecterLecteurs::closeEvent(QCloseEvent *event)
{
    // TODO : Est-ce une fermeture propre ?
    // Switch off ReaderDetector betwen close
    emit sig_switchOff_readerDetector();
    event->accept();
}

void DetecterLecteurs::on_onPushButton_clicked()
{
    // Switch on readerDetector
    QString address = DetecterLecteurs::ui->addressLineEdit->text();
    unsigned int port = DetecterLecteurs::ui->portSpinBox->value();
    emit sig_switchOn_readerDetector(address, port);
}

void DetecterLecteurs::on_offPushButton_clicked()
{
    // Switch off readerDetector
    emit sig_switchOff_readerDetector();
}

void DetecterLecteurs::occuredSignal(QString signal)
{
    qDebug() << "Fenetre : occuredSignal :" << signal << endl
            //<< "readerDetector value : "
            //<< QString().sprintf("%8p", readerDetector)
            << endl;
}
