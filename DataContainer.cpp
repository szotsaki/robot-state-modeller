#include "DataContainer.h"
#include <vector>
#include "Data/Data.h"
#include "Data/DataCommandOnly.h"
#include "Data/DataVecStateOnly.h"

DataContainer::DataContainer()
{
    data[kD_Sync] = new DataCommandOnly<int>();
    data[kD_Estop] = new DataCommandOnly<int>();
    data[kD_Velocity] = new Data<double>();
    data[kD_Accel] = new Data<double>();
    data[kD_SteerAng] = new Data<double>();
    data[kD_LightSen] = new DataVecStateOnly< int >();
    data[kD_DistSen] = new DataVecStateOnly< double >();
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

std::string DataContainer::getDataIdText(const dataId_t dataId) const
{
    return dataIdTexts[dataId];
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

std::vector<dataId_t> DataContainer::getAllDataIds() const
{
    std::vector<dataId_t> result;
    for (size_t i = 0; i < data.size(); ++i)
    {
        result.push_back(static_cast<dataId_t>(i));
    }
    return result;
}

std::vector<dataId_t> DataContainer::getTimeChartDataIds() const
{
    std::vector<dataId_t> result;
    for (size_t i = 0; i < data.size(); ++i)
    {
        dataId_t id = static_cast<dataId_t>(i);
        dataValueType_t type = dataValueTypes[id];
        if (type == kDvt_Int32 || type == kDvt_Float64)
        {
            result.push_back(id);
        }
    }
    return result;
}

std::vector<dataId_t> DataContainer::getBarChartDataIds() const
{
    std::vector<dataId_t> result;
    for (size_t i = 0; i < data.size(); ++i)
    {
        dataId_t id = static_cast<dataId_t>(i);
        dataValueType_t type = dataValueTypes[id];
        if (type == kDvt_Int32Vec || type == kDvt_Float64Vec)
        {
            result.push_back(id);
        }
    }
    return result;
}
