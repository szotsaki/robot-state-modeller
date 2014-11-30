#include "Monitor.h"
#include "ValueWrapperFactory.h"

void Monitor::receive()
{
    QDataStream &inStream = network.getReceiveStream();
    // get msg size
    // while (inStream.available >= msg size)
    while (inStream.status() == QDataStream::Ok)
    {
        dataId_t dataId;
        inStream >> dataId;
        dataContainer.receive(dataId, inStream);
    }
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
    ValueWrapper *wrapper = ValueWrapperFactory::create(kD_Estop, "");
    send(kD_Estop, *wrapper);
    delete wrapper;
}

void Monitor::drawBarChart(const dataId_t dataId, QCustomPlot *customPlot)
{
    dataContainer.drawBarChart(dataId, customPlot);
}

void Monitor::drawTimeChart(const dataId_t dataId, QCustomPlot *customPlot)
{
    dataContainer.drawTimeChart(dataId, customPlot);
}

std::string Monitor::getDataIdText(const dataId_t dataId) const
{
    return dataContainer.getDataIdText(dataId);
}

std::string Monitor::getDataValueText(const dataId_t dataId) const
{
    return dataContainer.getDataValueText(dataId);
}

void Monitor::drawChart(const dataId_t dataId, QCustomPlot *customPlot)
{
    const std::vector<dataId_t> timeChartIds = getTimeChartDataIds();
    const std::vector<dataId_t> barChartIds = getBarChartDataIds();

    if (std::find(timeChartIds.cbegin(), timeChartIds.cend(), dataId) != timeChartIds.cend()) {
        drawTimeChart(dataId, customPlot);
    } else if (std::find(barChartIds.cbegin(), barChartIds.cend(), dataId) != barChartIds.cend()) {
        drawBarChart(dataId, customPlot);
    }
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
