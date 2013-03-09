#include "readerclient.h"

ReaderClient::ReaderClient(const Reader& reader, QObject *parent)
    : QObject(parent), _reader(reader)
{
}

const Reader& ReaderClient::reader() const
{
    return _reader;
}
