#ifndef CLIENTTCPWINDOW_H
#define CLIENTTCPWINDOW_H

#include <QWidget>
#include <QAbstractSocket>
#include "clienttcp.h"

namespace Ui {
    class ClientTcpWindow;
}

class ClientTcpWindow : public QWidget {
    Q_OBJECT
public:
    ClientTcpWindow(QWidget *parent = 0);
    ~ClientTcpWindow();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_connectPushButton_clicked();

    void clientTcpWindow_connected();
    void clientTcpWindow_disconnected();
    void clientTcp_error(QAbstractSocket::SocketError socketError);

private:
    Ui::ClientTcpWindow *ui;
    ClientTcp *clientTcp;
};

#endif // CLIENTTCPWINDOW_H
