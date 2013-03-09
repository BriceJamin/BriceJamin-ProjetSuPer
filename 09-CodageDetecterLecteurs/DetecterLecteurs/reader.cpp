#include "reader.h"

Reader::Reader(int number, int placeId, QString address, bool isConnected)
{
    _number = number;
    _placeId = placeId;
    _address = address;
    _isConnected = isConnected;
}

unsigned int Reader::number() const
{
    return _number;
}

unsigned int Reader::placeId() const
{
    return _placeId;
}

QString Reader::address() const
{
    return _address;
}

bool Reader::isConnected() const
{
    return _isConnected;
}

void Reader::number(unsigned int number)
{
    _number = number;
}

void Reader::placeId(unsigned int placeId)
{
    _placeId = placeId;
}

void Reader::address(QString address)
{
    _address = address;
}

void Reader::isConnected(bool isConnected)
{
    _isConnected = isConnected;
}

