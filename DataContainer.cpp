#include "DataContainer.h"
#include <vector>
#include "Data/Data.h"
#include "Data/DataCommandOnly.h"
#include "Data/DataStateOnly.h"

DataContainer::DataContainer()
{
    // TODO: add all telemetry data here.
    data[kD_Sync] = new DataCommandOnly<int>();
    data[kD_Estop] = new DataCommandOnly<int>();
    data[kD_Velocity] = new Data<double>();
    data[kD_Accel] = new Data<double>();
    data[kD_SteerAng] = new Data<double>();
    data[kD_LightSen] = new DataStateOnly< std::vector<int> >();
    data[kD_DistSen] = new DataStateOnly< std::vector<double> >();
    data[kD_SmState] = new Data<int>();
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
    Q_UNUSED(outStream);
    // TODO: implement
}

std::string DataContainer::getDataValueText(const dataId_t dataId) const
{
    return data[dataId]->getValueText();
}

void DataContainer::drawTimeChart(const dataId_t dataId) const
{
    data[dataId]->drawTimeChart();
}

void DataContainer::drawBarChart(const dataId_t dataId) const
{
    data[dataId]->drawBarChart();
}
