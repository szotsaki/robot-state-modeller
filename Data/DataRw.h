#ifndef DATA_RW_H_
#define DATA_RW_H_

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

public:
    Command<T> command;
    QCircularBuffer< State<T> > states;

    virtual void setCommand(const ValueWrapper &value);
    virtual void sendCommand(QDataStream &outStream,
                             const bool onlyInProgress = false) override;
    virtual void deserialise(QDataStream &inStream) override;
    virtual void updateCommand() override;

    virtual std::string getValueText() const;
    virtual void drawTimeChart() const;
    virtual void drawBarChart() const;
};

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
        //oss << states.at(0);
        return oss.str();
    }
    return std::string();
}

template<typename T>
inline void DataRw<T>::drawTimeChart() const
{
    // TODO
}

template<typename T>
inline void DataRw<T>::drawBarChart() const
{
    // Cannot draw since state does not contain vector types.
}

#endif // DATA_RW_H_
