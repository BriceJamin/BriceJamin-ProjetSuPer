#ifndef READER_H
#define READER_H

#include <QObject>
#include "readerdata.h"

class Reader : public QObject
{
    Q_OBJECT

signals:
    void sig_disconnected();

public:
    explicit Reader(const ReaderData&, QObject *parent = 0);
    const ReaderData& data() const;

private:
    ReaderData _data;
};

#endif // READERCLIENT_H
