#ifndef DATA_RW_H_
#define DATA_RW_H_

#include <algorithm>
#include <sstream>
#include <QDataStream>

#include "../QCircularBuffer.h"
#include "../ValueWrapper.h"
#include "Command.h"
#include "DataInterface.h"
#include "State.h"

/**
 * Readable and writable telemetry data.
 * Uses a simple type for its value.
 */
template<typename T>
class DataRw : public DataInterface
{
    typedef State< T >  _MyState;

public:
    Command<T> command;
    QCircularBuffer< State<T> > states;

    DataRw();

    virtual void setCommand(const ValueWrapper &value);
    virtual void sendCommand(QDataStream &outStream,
                             const bool onlyInProgress = false) override;
    virtual void deserialise(QDataStream &inStream) override;
    virtual void updateCommand() override;

    virtual std::string getValueText() const;
    virtual void drawTimeChart(QCustomPlot *customPlot) const;
    virtual void drawBarChart(QCustomPlot *customPlot) const;
};

template<typename T>
inline DataRw<T>::DataRw()
{
    states.setCapacity(ROB_MON_DATA_SIZE);
}

template<typename T>
inline void DataRw<T>::setCommand(const ValueWrapper &value)
{
    command.setValue(value);
}

template<typename T>
inline void DataRw<T>::sendCommand(QDataStream &outStream,
                                   const bool onlyInProgress)
{
    if (!onlyInProgress || command.inProgess())
    {
        command.serialise(outStream);
    }
}

template<typename T>
inline void DataRw<T>::deserialise(QDataStream &inStream)
{
    State<T> s;
    s.deserialise(inStream);
    states.push_back(s);
}

template<typename T>
inline void DataRw<T>::updateCommand()
{
    const T value = states.at(0).getValue();
    command.update(value);
}

template<typename T>
inline std::string DataRw<T>::getValueText() const
{
    if (!states.empty())
    {
        std::ostringstream oss;
        oss << states.at(0).getValue();
        return oss.str();
    }
    return std::string();
}

template<typename T>
inline void DataRw<T>::drawTimeChart(QCustomPlot *customPlot) const
{
    QVector<double> x(states.size());
    QVector<double> y(states.size());
    double minY = std::numeric_limits<double>::max();
    double maxY = -minY;
    for (int i = 0; i < states.size(); ++i)
    {
        x[i] = static_cast<double>(i);	// TODO: time
        y[i] = static_cast<double>(states[i].getValue());
        maxY = std::max(y[i], maxY);
        minY = std::min(y[i], minY);
    }
    customPlot->graph(0)->setData(x, y);
    // Set axes ranges.
    customPlot->xAxis->setRange(0, states.size());
    customPlot->yAxis->setRange(minY, maxY);
    customPlot->replot();
}

template<typename T>
inline void DataRw<T>::drawBarChart(QCustomPlot *customPlot) const
{
    Q_UNUSED(customPlot)
    // Cannot draw since state does not contain vector types.
}

#endif // DATA_RW_H_
