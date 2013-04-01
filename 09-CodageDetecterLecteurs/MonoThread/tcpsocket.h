#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>
#include <QNetworkProxy>
#include <QAuthenticator>

class TcpSocket : public QTcpSocket
{
Q_OBJECT
public:
    explicit TcpSocket(QObject *parent = 0);

private slots:
    void slot_connected();
    void slot_disconnected();
    void slot_error(QAbstractSocket::SocketError);
    void slot_hostFound();
    void slot_proxyAuthenticationRequired(QNetworkProxy,QAuthenticator*);
    void slot_stateChanged(QAbstractSocket::SocketState);
    void slot_aboutToClose();
    void slot_readyRead();
    void slot_readChannelFinished();
    void slot_bytesWritten(qint64);
};

#endif // TCPSOCKET_H
