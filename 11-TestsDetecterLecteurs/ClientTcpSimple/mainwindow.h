#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

#include "clienttcpwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_newClientPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QList<ClientTcpWindow*> clientTcpWindowList;
};

#endif // MAINWINDOW_H
