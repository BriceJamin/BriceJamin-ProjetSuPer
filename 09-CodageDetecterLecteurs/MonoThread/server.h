#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QString address, unsigned int port, QObject *parent = 0);
    
signals:
    void sig_switchedOn();
    void sig_switchedOff();

    void sig_intruderEjected();
    void sig_readerConnected();
    void sig_readerDisconnected();

    void sig_tcpError();
    void sig_sqlError();

    void sig_tcpClientError();

public slots:
    void slot_switchOn();
    void slot_switchOff();

private:
    QString _address;
    unsigned int _port;
};

#endif // SERVER_H
