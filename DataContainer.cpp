#include "DataContainer.h"

DataContainer::DataContainer():
    data(std::array<DataInterface, 0>())
{
}

DataContainer::~DataContainer()
{

}

void DataContainer::receive(int ID, QDataStream& stream)
{

}

void DataContainer::sendCommand(int ID, QDataStream& stream)
{

}

void DataContainer::sync(QDataStream& stream)
{

}
