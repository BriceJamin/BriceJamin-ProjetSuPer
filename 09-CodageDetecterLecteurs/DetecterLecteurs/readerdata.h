#ifndef READERDATA_H
#define READERDATA_H

#include <QString>

class ReaderData
{
public:
    ReaderData(int, int, QString, bool);
    ReaderData(const ReaderData&);

    unsigned int number() const;
    unsigned int placeId() const;
    QString address() const;
    bool isConnected() const;

    void number(unsigned int);
    void placeId(unsigned int);
    void address(QString);
    void isConnected(bool);

private:
    unsigned int _number;
    unsigned int _placeId;
    QString _address;
    bool _isConnected;
};

#endif // READERDATA_H
