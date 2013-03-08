#ifndef READERCLIENT_H
#define READERCLIENT_H

#include <QObject>

class ReaderClient : public QObject
{
    Q_OBJECT

signals:
public slots:

public:
    explicit ReaderClient(Reader reader, QObject *parent = 0);
    int number() const;
    int placeId() const;
    QString address() const;
    bool isConnected() const;

private:
    Reader reader;
};

#endif // READERCLIENT_H
