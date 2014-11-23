#include "DataInterface.h"

QDataStream & operator >>(QDataStream &inStream, dataId_t &dataId)
{
    inStream >> (quint32&)dataId;
    return inStream;
}

DataInterface::~DataInterface()
{
}
