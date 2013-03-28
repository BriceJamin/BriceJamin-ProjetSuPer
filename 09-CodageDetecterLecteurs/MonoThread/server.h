#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Server : public QTcpServer
{
    Q_OBJECT

signals:
    void sig_switchedOn();
    void sig_switchedOff();

    void sig_portChanged(quint16);
    void sig_addressChanged(QString);

    void sig_intruderEjected();
    void sig_readerConnected();
    void sig_readerDisconnected();

    void sig_tcpError();
    void sig_sqlError();

    void sig_tcpClientError();

public slots:
    void switchOn();
    void switchOff();
    bool setAddress(QString);
    bool setPort(QString);

public:
    explicit Server(QString address, QString port, QObject *parent = 0);
    ~Server();

    QString address();
    quint16 port();

private:
    QHostAddress _address;
    quint16 _port;
};

#endif // SERVER_H
