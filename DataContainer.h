#ifndef DATA_CONTAINER_H_
#define DATA_CONTAINER_H_

#include <array>
#include <QDataStream>

#include "DataInterface.h"

class DataContainer
{

public:
    DataInterface *dataInterface;

	DataContainer();
    ~DataContainer();
	void receive(int ID, QDataStream& stream);
	void sendCommand(int ID, QDataStream& stream);
	void sync(QDataStream& stream);

private:
    const std::array<DataInterface, 0> data;

};
#endif // DATA_CONTAINER_H_
