#ifndef SERVER_H
#define SERVER_H

#include "tcpserver.h"

/*
     Créer une classe pour gérer la communication de(s) client(s)
     C'est dans cette classe que les instanciations dynamiques et
    les moveToThread auront lieu.
     S'y connecter et ne jamais s'en servir, les signaux doivent
    faire le boulot.
      Il faudra lui donner les socketDescriptor, le signal
    TcpServer::incommingConnection conviendra parfaitement
      L'IHM peut vouloir savoir qu'une nouvelle connexion est
    en cour, dans ce cas créer un nouveau signal dans Server,
    connecté sur TcpServer::incomingConnection. L'IHM ne devant
    pas accéder au socket descriptor, le nouveau signal du Server
    ne devra avoir aucun paramètre.
*/

class Server : public QObject
{
    Q_OBJECT

public:
    enum SwitchOnState
    {
        Success,
        AddressNotAvailableError,
        PortProtectedError,
        PortAlreadyInUseError,
        UnknownError
    };

signals:
    void sig_switchedOn();
    void sig_switchedOff();

    void sig_portChanged(quint16);
    void sig_addressChanged(QString);

    void sig_intruderEjected();
    void sig_readerConnected();
    void sig_readerDisconnected();

    void sig_stopAllClientManager();

    void sig_tcpError();
    void sig_sqlError();

    void sig_tcpClientError();

public slots:
    SwitchOnState switchOn();
    void switchOff();
    bool setAddress(QString);
    bool setPort(QString);
    void killAllCommunications();

public:
    explicit Server(QString address, QString port, QObject *parent = 0);
    ~Server();

    QString address();
    quint16 port();

private:
    bool _setAddress(QString);
    bool _setPort(QString);

    QHostAddress _address;
    quint16 _port;
    TcpServer _server;
};

QDebug operator<<(QDebug, const Server::SwitchOnState&);

#endif // SERVER_H
