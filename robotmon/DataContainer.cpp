#include "DataContainer.h"
#include <vector>
#include "Data/DataRw.h"
#include "Data/DataWriteOnly.h"
#include "Data/DataVecReadOnly.h"

DataContainer::DataContainer()
{
    data[kD_Sync] = new DataWriteOnly<int>();
    data[kD_Estop] = new DataWriteOnly<int>();
    data[kD_Velocity] = new DataRw<double>();
    data[kD_Accel] = new DataRw<double>();
    data[kD_SteerAng] = new DataRw<double>();
    data[kD_LightSen] = new DataVecReadOnly< int >();
    data[kD_DistSen] = new DataVecReadOnly< double >();
    data[kD_SmState] = new DataRw<int>();
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
    data[dataId]->setCommand(value);
    sendCommandImpl(dataId, outStream);
}

bool DataContainer::isReadOnly(const dataId_t dataId) const
{
    return data[dataId]->isReadOnly();
}

void DataContainer::sendCommandImpl(const dataId_t dataId,
                                    QDataStream &outStream)
{
    const qint64 startPos = outStream.device()->size();
    qint32 msgSize = 0;
    outStream << msgSize;
    outStream << (int32_t)dataId;    // Serialize data identifier.
    data[dataId]->sendCommand(outStream, false);
    const qint64 endPos = outStream.device()->size();
    outStream.device()->seek(startPos);
    msgSize = endPos - startPos;
    outStream << msgSize;
    outStream.device()->seek(endPos);
}

void DataContainer::sync(QDataStream &outStream)
{
    outStream << (int32_t)8;
    outStream << (int32_t)kD_Sync;
    for (size_t id = 0; id < data.size(); ++id)
    {
        if (data[id]->inProgress())
        {
            dataId_t dataId = static_cast<dataId_t>(id);
            sendCommandImpl(dataId, outStream);
        }
    }
}

std::string DataContainer::getDataIdText(const dataId_t dataId) const
{
    return dataIdTexts[dataId];
}

std::string DataContainer::getDataValueText(const dataId_t dataId) const
{
    return data[dataId]->getValueText();
}

void DataContainer::drawTimeChart(const dataId_t dataId,
                                  QCustomPlot *customPlot) const
{
    customPlot->xAxis->setLabel("Time");
    customPlot->yAxis->setLabel(dataIdTexts[dataId].c_str());
    data[dataId]->drawTimeChart(customPlot);
}

void DataContainer::drawBarChart(const dataId_t dataId, QCustomPlot *customPlot) const
{
    data[dataId]->drawBarChart(customPlot);
}

std::vector<dataId_t> DataContainer::getAllDataIds() const
{
    std::vector<dataId_t> result;
    for (size_t i = 2; i < data.size(); ++i)
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
