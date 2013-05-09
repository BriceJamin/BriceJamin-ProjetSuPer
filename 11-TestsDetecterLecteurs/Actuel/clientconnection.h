#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QObject>
#include "tcpsocket.h"
#include "reader.h"

class ClientConnection : public QObject
{
Q_OBJECT
signals:
    void sig_connected(); // TODO : Inutile car précède dans tous les cas sig_isAReader et sig_isNotAReader. N'est de toute façon jamais appelé car récupération de la socket via setdescripteur : la socket est déjà connectée. A supprimer.
    void sig_isAReader(Reader);
    void sig_isNotAReader(QString);
    void sig_dataRead(QString);
    void sig_disconnected();
    void sig_closed(); // TODO : Inutile car en cas de rupture de connexion disconnected est aussi émis. A supprimer ?
    void sig_error();

public:
    explicit ClientConnection(int);
    ~ClientConnection();

public slots:
    void open(); // TODO : Seul server (ou le thread ?) doit y avoir accès, la rendre privée et ajouter server en amis seulement sur cette méthode.
    void close();

private:
    TcpSocket _tcpSocket;
    int _socketDescriptor;

private slots:
    void filter();
    void readyRead();
};

#endif // CLIENTCONNECTION_H
