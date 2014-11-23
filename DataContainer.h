#ifndef DATA_CONTAINER_H_
#define DATA_CONTAINER_H_

#include <array>
#include <vector>
#include <QDataStream>

#include "Data/DataInterface.h"
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

    std::vector<dataId_t> getAllDataIds() const;
    std::vector<dataId_t> getTimeChartDataIds() const;
    std::vector<dataId_t> getBarChartDataIds() const;

    std::string getDataValueText(const dataId_t dataId) const;
    void drawTimeChart(const dataId_t dataId) const;
    void drawBarChart(const dataId_t dataId) const;

private:
    std::array<DataInterface *, kD_NumIds> data;

};
#endif // DATA_CONTAINER_H_
