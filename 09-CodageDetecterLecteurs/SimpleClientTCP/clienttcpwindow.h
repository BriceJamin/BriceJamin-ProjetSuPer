#ifndef CLIENTTCPWINDOW_H
#define CLIENTTCPWINDOW_H

#include <QDialog>
#include <QAbstractSocket>
#include "clienttcp.h"

namespace Ui {
    class ClientTcpWindow;
}

class ClientTcpWindow : public QWidget {
    Q_OBJECT
public:
    ClientTcpWindow(QString serverAddress, QString serverPort, QWidget *parent = 0);
    ~ClientTcpWindow();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_connectPushButton_clicked();

    void clientTcp_connected();
    void clientTcp_disconnected();
    void clientTcp_error(QAbstractSocket::SocketError socketError);

    void on_disconnectPushButton_clicked();

private:
    Ui::ClientTcpWindow *ui;
    ClientTcp *clientTcp;
};

#endif // CLIENTTCPWINDOW_H
