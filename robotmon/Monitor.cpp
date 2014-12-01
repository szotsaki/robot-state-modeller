#include "Monitor.h"
#include "ValueWrapperFactory.h"

Monitor::Monitor() :
    blockSize(0)
{
    connect(&network, &Network::errorOccurred, this, &Monitor::errorOccurred);
    connect(&network, &Network::readyRead, this, &Monitor::receive);

    network.connect();
}

void Monitor::receive()
{
    QDataStream &inStream = network.getReceiveStream();
    QIODevice *socket = inStream.device();

    // It's a new block
    if (blockSize == 0) {
        // There's not enough bytes arrived to determine the size
        if (socket->bytesAvailable() < (int) sizeof(qint32)) {
            return;
        }

        // Computing blockSize
        inStream >> blockSize;
    }

    if (socket->bytesAvailable() < (int) (blockSize - sizeof(qint32))) {
        return;
    }

    // Process the received data
    dataId_t dataId;
    inStream >> dataId;
    dataContainer.receive(dataId, inStream);
    emit newValueReceived(dataId);

    // Maybe we got the first bytes of a next packet
    blockSize = 0;
    if (socket->bytesAvailable() > 0) {
        QTimer::singleShot(0, this, SLOT(receive()));
    }
}

void Monitor::send(const dataId_t dataId, const ValueWrapper &value)
{
    QDataStream *inStream = network.getSendStream();
    dataContainer.sendCommand(dataId, value, *inStream);
    network.send();
    delete inStream;
}

void Monitor::sync()
{
    QDataStream *inStream = network.getSendStream();
    dataContainer.sync(*inStream);
    network.send();
    delete inStream;
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

bool Monitor::isReadOnly(const dataId_t dataId) const
{
    return dataContainer.isReadOnly(dataId);
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
