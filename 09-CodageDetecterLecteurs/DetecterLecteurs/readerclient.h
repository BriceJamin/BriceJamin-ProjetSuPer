#ifndef READERCLIENT_H
#define READERCLIENT_H

#include <QObject>

class ReaderClient : public QObject
{
    Q_OBJECT
public:
    explicit ReaderClient(QObject *parent = 0);
    
signals:
public slots:
    
};

#endif // READERCLIENT_H
