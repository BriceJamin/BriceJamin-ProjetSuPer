#ifndef TCPSERVERTHREAD_H
#define TCPSERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "reader.h"

class TcpServerThread : public QThread
{
Q_OBJECT
public:
    explicit TcpServerThread(int socketDescriptor, QObject *parent);
    ~TcpServerThread();
    void run();

signals:
    void sig_errorOccurred(QString);
    void sig_intruderEjected(QString clientAddress);
    void sig_readerConnected(Reader* reader);
    void sig_readerDisconnected(Reader* reader);

private slots:
    void slot_socketDisconnected();

private:
    int socketDescriptor;
    Reader reader;
};

#endif // TCPSERVERTHREAD_H
