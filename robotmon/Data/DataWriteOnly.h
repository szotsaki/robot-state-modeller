#ifndef DATA_WRITE_ONLY_H_
#define DATA_WRITE_ONLY_H_

#include <QDataStream>

#include "../ValueWrapper.h"
#include "Command.h"
#include "DataInterface.h"

/**
 * Write-only telemetry data.
 * Uses a simple type for its value.
 * Write-only means you can only send commands to modify
 * it's value (if any) but has no feedback from the robot.
 */
template<typename T>
class DataWriteOnly : public DataInterface
{

public:
    Command<T> command;

    virtual void setCommand(const ValueWrapper &value);
    virtual void sendCommand(QDataStream &outStream,
                             const bool onlyInProgress = false) override;
    virtual void deserialise(QDataStream &inStream) override;
    virtual void updateCommand() override;

    virtual std::string getValueText() const { return std::string(); }
    virtual void drawTimeChart(QCustomPlot *customPlot) const;
    virtual void drawBarChart() const;
};

template <typename T>
inline void DataWriteOnly<T>::setCommand(const ValueWrapper &value)
{
    command.setValue(value);
}

template <typename T>
inline void DataWriteOnly<T>::sendCommand(QDataStream &outStream,
                                          const bool onlyInProgress)
{
    if (!onlyInProgress || command.inProgess())
    {
        command.serialise(outStream);
    }
}

template <typename T>
inline void DataWriteOnly<T>::deserialise(QDataStream &)
{
    // No states, nothing to do.
}

template <typename T>
inline void DataWriteOnly<T>::updateCommand()
{
    // No states, nothing to update with.
}

template<typename T>
inline void DataWriteOnly<T>::drawTimeChart(QCustomPlot *) const
{
    // No states, nothing to do.
}

template<typename T>
inline void DataWriteOnly<T>::drawBarChart() const
{
    // No states, nothing to do.
}

#endif // DATA_WRITE_ONLY_H_
