#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>

#include "persontupleview.h"
#include "testlayout.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QHBoxLayout *_layout;
    PersonTupleView* _personTupleView;
    TestLayout *_testLayout;

private slots:
    void on_addPersonPushButton_clicked();
};

#endif // MAINWINDOW_H
