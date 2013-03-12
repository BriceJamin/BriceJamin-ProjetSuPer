#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

#include "clienttcp.h"

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
    void on_connectPushButton_clicked();

    void clientTcp_connected();
    void clientTcp_disconnected();
    void clientTcp_error(QAbstractSocket::SocketError socketError);

private:
    Ui::MainWindow *ui;
    ClientTcpWindow *clientTcpWindow;
};

#endif // MAINWINDOW_H
