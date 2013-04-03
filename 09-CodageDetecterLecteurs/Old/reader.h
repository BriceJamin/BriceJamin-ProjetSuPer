#ifndef READER_H
#define READER_H

#include <QString>

class Reader
{
public:
    Reader(int=0, int=0, QString="", bool=false);
    Reader(const Reader&);

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

#endif // READER_H
