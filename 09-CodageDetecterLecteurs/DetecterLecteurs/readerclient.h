#ifndef READERCLIENT_H
#define READERCLIENT_H

#include <QObject>
#include "reader.h"

class ReaderClient : public QObject
{
    Q_OBJECT

signals:
public slots:

public:
    explicit ReaderClient(const Reader&, QObject *parent = 0);
    const Reader& reader() const;

private:
    Reader _reader;
};

#endif // READERCLIENT_H
