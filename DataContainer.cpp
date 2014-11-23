#include "DataContainer.h"

DataContainer::DataContainer():
    data(std::array<DataInterface *, 0>())
{
    // TODO: add all telemetry data here.
}

DataContainer::~DataContainer()
{
    for (DataInterface *pData : data)
    {
        delete pData;
    }
}

void DataContainer::receive(const dataId_t dataId, QDataStream &inStream)
{
    data[dataId]->deserialise(inStream);
}

void DataContainer::sendCommand(const dataId_t dataId,
                                const ValueWrapper &value,
                                QDataStream &outStream)
{
    outStream << dataId;    // Serialize data identifier.
    data[dataId]->sendCommand(value, outStream, false);
}

void DataContainer::sync(QDataStream &outStream)
{
    outStream;  // silent unused warning.
    // TODO: implement.
}
