#ifndef TCPSERVERTHREAD_H
#define TCPSERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "readerclient.h"

class TcpServerThread : public QThread
{
Q_OBJECT
public:
    explicit TcpServerThread(int socketDescriptor, QObject *parent);

    void run();

signals:
    void  sig_errorOccured(QString);
    void sig_intruderDetected(QString clientAddress);
    /* (?) Si un reader est detecte, un reader devrait etre envoye, pas un readerClient */
    /* TODO (?) : Renommer Reader en ReaderData et ReaderClient en Reader */
    void sig_readerDetected(const ReaderClient& readerClient);

public slots:

private:
    int socketDescriptor;
};

#endif // TCPSERVERTHREAD_H
