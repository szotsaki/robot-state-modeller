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

    Monitor();

    // Network-related functions.
    void receive();
    void send(const dataId_t dataId, const ValueWrapper &value);

    // UI-related functions.
    std::string getDataIdText(const dataId_t dataId) const;
    std::string getDataValueText(const dataId_t dataId) const;
    /**
     * Display data on a diagram.
     * @param dataId	 Data to display.
     * @param customPlot Plot to draw on. Draws to the graph with 0 index.
     */
    void drawChart(const dataId_t dataId, QCustomPlot *customPlot);

    // Query data identifiers.
    std::vector< dataId_t > getAllDataIds() const;

public slots:
    void sync();
    void emergencyStop();

signals:
    void newValueReceived(dataId_t);
    void errorOccurred(const QString &);

private:
    DataContainer dataContainer;
    Network network;
    qint32 blockSize;

    void drawTimeChart(const dataId_t dataId, QCustomPlot *customPlot);
    void drawBarChart(const dataId_t dataId, QCustomPlot *customPlot);
    std::vector< dataId_t > getTimeChartDataIds() const;
    std::vector<dataId_t> getBarChartDataIds() const;
};
#endif // MONITOR_H_
