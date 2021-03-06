#ifndef DETECTERLECTEURS_H
#define DETECTERLECTEURS_H

#include <QMainWindow>
#include <QCloseEvent>

#include "readerdetector.h"

namespace Ui {
    class DetecterLecteurs;
}

class DetecterLecteurs : public QMainWindow {
    Q_OBJECT

signals:
    void sig_switchOn_readerDetector(QString address, unsigned int port);
    void sig_switchOff_readerDetector();

public:
    DetecterLecteurs(ReaderDetector* rd, QWidget *parent = 0);
    ~DetecterLecteurs();

public slots:
    void readerDetector_switchedOn();
    void readerDetector_switchedOff();

    void readerDetector_intruderEjected(QString address);
    void readerDetector_readerConnected(Reader*);
    void readerDetector_readerDisconnected(Reader*);

    void readerDetector_errorOccurred(QString error);
    void readerDetector_destroyed();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *event);

private slots:
    void on_onPushButton_clicked();
    void on_offPushButton_clicked();

private:
    void display(QString);

    Ui::DetecterLecteurs *ui;
    ReaderDetector* readerDetector;
};

#endif // DETECTERLECTEURS_H
