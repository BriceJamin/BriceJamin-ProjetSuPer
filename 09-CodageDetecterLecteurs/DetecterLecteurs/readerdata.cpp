#include "readerdata.h"

ReaderData::ReaderData(int number, int placeId, QString address, bool isConnected)
{
    _number = number;
    _placeId = placeId;
    _address = address;
    _isConnected = isConnected;
}

ReaderData::ReaderData(const ReaderData& data)
{
    _number = data._number;
    _placeId = data._placeId;
    _address = data._address;
    _isConnected = data._isConnected;
}

unsigned int ReaderData::number() const
{
    return _number;
}

unsigned int ReaderData::placeId() const
{
    return _placeId;
}

QString ReaderData::address() const
{
    return _address;
}

bool ReaderData::isConnected() const
{
    return _isConnected;
}

void ReaderData::number(unsigned int number)
{
    _number = number;
}

void ReaderData::placeId(unsigned int placeId)
{
    _placeId = placeId;
}

void ReaderData::address(QString address)
{
    _address = address;
}

void ReaderData::isConnected(bool isConnected)
{
    _isConnected = isConnected;
}

