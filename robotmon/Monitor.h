#ifndef MONITOR_H_
#define MONITOR_H_

#include <QObject>

#include "QCustomPlot.h"
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
    std::string getDataIdText(const dataId_t dataId) const;
    std::string getDataValueText(const dataId_t dataId) const;
    /**
     * Display data in a time chart diagram.
     * @param dataId	 Data to display.
     * @param customPlot Plot to draw on. Draws to the graph with 0 index.
     */
    void drawTimeChart(const dataId_t dataId, QCustomPlot *customPlot);
    void drawBarChart(const dataId_t dataId);

    // Query data identifiers.
    std::vector< dataId_t > getAllDataIds() const;
    std::vector< dataId_t > getTimeChartDataIds() const;
    std::vector< dataId_t > getBarChartDataIds() const;

public slots:
    void sync();
    void emergencyStop();

signals:
    void newValueReceived(dataId_t dataId);

private:
    DataContainer dataContainer;
    Network network;

};
#endif // MONITOR_H_
