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

std::vector<dataId_t> Monitor::getAllDataIds() const
{
    return dataContainer.getAllDataIds();
}

std::vector<dataId_t> Monitor::getTimeChartDataIds() const
{
    return dataContainer.getTimeChartDataIds();
}

std::vector<dataId_t> Monitor::getBarChartDataIds() const
{
    return dataContainer.getBarChartDataIds();
}
