#include "Monitor.h"


void Monitor::receive()
{
    QDataStream &inStream = network.getReceiveStream();
    dataId_t dataId;
    inStream >> dataId;
    dataContainer.receive(dataId, inStream);
}

void Monitor::send(const dataId_t dataId)
{
    dataContainer.sendCommand(dataId, network.getSendStream());
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
