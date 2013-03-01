#ifndef DETECTERLECTEURS_H
#define DETECTERLECTEURS_H

#include <QMainWindow>

namespace Ui {
    class DetecterLecteurs;
}

class DetecterLecteurs : public QMainWindow {
    Q_OBJECT
public:
    DetecterLecteurs(QWidget *parent = 0);
    ~DetecterLecteurs();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DetecterLecteurs *ui;
};

#endif // DETECTERLECTEURS_H
