#ifndef DATA_CONTAINER_H_
#define DATA_CONTAINER_H_

#include <array>
#include <QDataStream>

#include "DataInterface.h"
#include "ValueWrapper.h"

class DataContainer
{

public:

	DataContainer();
    ~DataContainer();
    void receive(const dataId_t dataId, QDataStream &inStream);
    void sendCommand(const dataId_t dataId,
                     const ValueWrapper &value,
                     QDataStream &outStream);
    void sync(QDataStream &outStream);

private:
    const std::array<DataInterface *, 0> data;

};
#endif // DATA_CONTAINER_H_
