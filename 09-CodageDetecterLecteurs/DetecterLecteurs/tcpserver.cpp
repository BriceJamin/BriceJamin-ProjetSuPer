#include "tcpserver.h"
#include "tcpserverthread.h"
TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{
}

void TcpServer::incomingConnection(int socketDescriptor)
 {
    emit sig_clientDetected();

    TcpServerThread *thread = new TcpServerThread(socketDescriptor, this);

    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(sig_error(QTcpSocket::SocketError)), this, SIGNAL(sig_error()));
    connect(thread, SIGNAL(sig_intruderDetected()), this, SIGNAL(sig_intruderDetected()));
    connect(thread, SIGNAL(sig_readerDetected()), this, SIGNAL(sig_readerDetected()));

    thread->start();
 }
