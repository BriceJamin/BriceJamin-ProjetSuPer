#ifndef CLIENTTCPWINDOW_H
#define CLIENTTCPWINDOW_H

#include <QWidget>

namespace Ui {
class ClientTcpWindow;
}

class ClientTcpWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit ClientTcpWindow(QWidget *parent = 0);
    ~ClientTcpWindow();
    
private:
    Ui::ClientTcpWindow *ui;
};

#endif // CLIENTTCPWINDOW_H
