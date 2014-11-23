#ifndef MONITOR_H_
#define MONITOR_H_

#include <QObject>

#include "DataContainer.h"
#include "Network.h"
#include "ValueWrapper.h"

class Monitor : public QObject
{
    Q_OBJECT

public:

    // Network-related functions.
    void receive();
    void send(const dataId_t dataId, const ValueWrapper &value);

    // UI-related functions.
    std::string getDataValueText(const dataId_t dataId) const;
    void drawTimeChart(const dataId_t dataId);
    void drawBarChart(const dataId_t dataId);

    // Query data identifiers.
    std::vector< dataId_t > getAllDataIds() const;
    std::vector< dataId_t > getTimeChartDataIds() const;
    std::vector< dataId_t > getBarChartDataIds() const;

public slots:
    void sync();
    void emergencyStop();

private:
    DataContainer dataContainer;
    Network network;

};
#endif // MONITOR_H_
