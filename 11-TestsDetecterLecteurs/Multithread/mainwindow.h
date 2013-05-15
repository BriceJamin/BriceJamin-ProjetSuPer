#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "a.h"
#include "thread.h"
namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow {
    Q_OBJECT
signals:
    void sig_killA();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QList<A*> aList;
    QList<Thread*> threadList;
private slots:
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
