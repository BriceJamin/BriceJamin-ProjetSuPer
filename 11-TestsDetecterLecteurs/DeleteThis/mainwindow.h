#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
signals:
    void killThemAll();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    int _nbThread;

private slots:
    void on_killThemAllPushButton_clicked();
    void on_pushButton_clicked();

    void thread_destroyed();
    void thread_finished();
    void thread_started();
    void thread_terminated();

    void a_destroyed();
};

#endif // MAINWINDOW_H
