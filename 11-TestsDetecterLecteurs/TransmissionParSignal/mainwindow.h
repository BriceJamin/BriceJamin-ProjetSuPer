#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "a.h"
#include "b.h"

namespace Ui {
    class MainWindow;
}

typedef A MyType;

class MainWindow : public QMainWindow {
    Q_OBJECT
signals:
    void signal(MyType*);
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    B b;

private slots:
    void on_pushButton_clicked();
    void slot(MyType*);
};

#endif // MAINWINDOW_H
