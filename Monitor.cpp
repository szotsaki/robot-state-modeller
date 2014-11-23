#include "Monitor.h"


void Monitor::receive()
{
    QDataStream &inStream = network.getReceiveStream();
    dataId_t dataId;
    inStream >> dataId;
    dataContainer.receive(dataId, inStream);
}

void Monitor::send(const dataId_t dataId, const ValueWrapper &value)
{
    dataContainer.sendCommand(dataId, value, network.getSendStream());
    network.send();
}

void Monitor::sync()
{
    dataContainer.sync(network.getSendStream());
    network.send();
}

void Monitor::emergencyStop()
{

}

void Monitor::drawBarChart(const dataId_t dataId)
{
    dataContainer.drawBarChart(dataId);
}

void Monitor::drawTimeChart(const dataId_t dataId)
{
    dataContainer.drawTimeChart(dataId);
}

std::string Monitor::getDataValueText(const dataId_t dataId) const
{
    return dataContainer.getDataValueText(dataId);
}

std::vector<dataId_t> Monitor::getTimeChartDataIds() const
{
    std::vector<dataId_t> result;
    return result;
}

std::vector<dataId_t> Monitor::getBarChartDataIds() const
{
    std::vector<dataId_t> result;
    return result;
}
