#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "server.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(Server* server, QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    Server* _server;
};

#endif // MAINWINDOW_H
