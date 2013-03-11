#include "reader.h"

Reader::Reader(const ReaderData& data, QObject *parent)
    : QObject(parent), _data(data)
{
}

const ReaderData& Reader::data() const
{
    return _data;
}
