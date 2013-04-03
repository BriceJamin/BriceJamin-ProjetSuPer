#ifndef TCPCLIENTMANAGER_H
#define TCPCLIENTMANAGER_H

#include <QTcpSocket>
#include <QTcpServer>
#include "reader.h"

class TcpClientManager : public QTcpSocket
{
Q_OBJECT

signals:
    void sig_intruderEjected(QString);
    void sig_readerConnected(Reader*);
    void sig_readerDisconnected(Reader*);
    void sig_tcpError(QString);
    void sig_sqlError(QString);
    void sig_finished();

public slots:
    void manage();

public:
    explicit TcpClientManager(int socketDescriptor, QTcpServer *parent);

private slots:
    void slot_tcpError();
    void slot_sqlError(QString);

private:
    void formatError(const QString&, QString&);

    int _socketDescriptor;
};

#endif // TCPCLIENTMANAGER_H
