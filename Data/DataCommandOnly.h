#ifndef DATA_COMMAND_ONLY_H_
#define DATA_COMMAND_ONLY_H_

#include <QDataStream>

#include "../ValueWrapper.h"
#include "Command.h"
#include "DataInterface.h"

template<typename T>
class DataCommandOnly : public DataInterface
{

public:
    Command<T> command;

    virtual void sendCommand(const ValueWrapper &value,
                             QDataStream &outStream,
                             const bool onlyInProgress = false) override;
    virtual void deserialise(QDataStream &inStream) override;
    virtual void updateCommand() override;

    virtual std::string getValueText() const { return std::string(); }
    virtual void drawTimeChart() const;
    virtual void drawBarChart() const;
};

template <typename T>
inline void DataCommandOnly<T>::sendCommand(const ValueWrapper &value,
                                     QDataStream &outStream,
                                     const bool onlyInProgress)
{
    if (!onlyInProgress || command.inProgess())
    {
        command.serialise(value, outStream);
    }
}

template <typename T>
inline void DataCommandOnly<T>::deserialise(QDataStream &)
{
    // No states, nothing to do.
}

template <typename T>
inline void DataCommandOnly<T>::updateCommand()
{
    // No states, nothing to update with.
}

template<typename T>
inline void DataCommandOnly<T>::drawTimeChart() const
{
    // No states, nothing to do.
}

template<typename T>
inline void DataCommandOnly<T>::drawBarChart() const
{
    // No states, nothing to do.
}

#endif // DATA_COMMAND_ONLY_H_
