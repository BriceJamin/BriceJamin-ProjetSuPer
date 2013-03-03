#ifndef DETECTERLECTEURS_H
#define DETECTERLECTEURS_H

#include <QMainWindow>
#include "readerdetector.h"

namespace Ui {
    class DetecterLecteurs;
}

class DetecterLecteurs : public QMainWindow {
    Q_OBJECT
public:
    DetecterLecteurs(ReaderDetector* rd, QWidget *parent = 0);
    ~DetecterLecteurs();

signals:
    void sig_occuredSignal(QString signal);

public slots:
    void readerDetector_switchedOn();
    void readerDetector_errorOccurred(QString error);
    void readerDetector_switchedOff();
    void readerDetector_clientDetected();
    void readerDetector_intruderDetected();
    void readerDetector_readerDetected();
    void readerDetector_destroyed();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_offPushButton_clicked();
    void on_onPushButton_clicked();
    void occuredSignal(QString signal);

private:
    Ui::DetecterLecteurs *ui;
    ReaderDetector* readerDetector;
};

#endif // DETECTERLECTEURS_H
