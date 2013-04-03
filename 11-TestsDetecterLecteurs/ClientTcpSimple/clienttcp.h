#ifndef CLIENTTCP_H
#define CLIENTTCP_H

#include <QTcpSocket>

class ClientTcp : public QTcpSocket
{
    Q_OBJECT
public:
    explicit ClientTcp(QObject *parent = 0);
    ~ClientTcp();
    QString getPeerAddress();
    bool setPeerAddress(const QString& address);

private:
    static int _clientsNumber;
    int _clientNumber;
    QString _address;
};

#endif // CLIENTTCP_H
