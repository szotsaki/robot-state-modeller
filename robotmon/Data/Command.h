#ifndef COMMAND_H_
#define COMMAND_H_

#include <QDataStream>
#include "../ValueWrapper.h"
#include "DataInterface.h"

enum class commandProgress_t
{
    kInProgress,
    kSuccess,
    kFailed
};

/**
 * This class represents a command which can be sent to the robot.
 * The command can have a meaningful payload, e.g. change acceleration to X,
 * but can also exist without real payload, e.g. emergency stop.
 * The class also tracks the progression of its command.
 */
template<typename T>
class Command
{

public:
    commandProgress_t progress;

    void setValue(const ValueWrapper &value);
    void serialise(QDataStream &outStream);
    void update(const T &state);
    bool inProgess();

private:
    T value;

};

template<typename T>
inline void Command<T>::setValue(const ValueWrapper &wrapper)
{
    value = static_cast< const TValue<T> & >(wrapper).getValue();
}

template<typename T>
inline void Command<T>::serialise(QDataStream &outStream)
{
    outStream << value;
    progress = commandProgress_t::kInProgress;

    const quint32 size = sizeof(quint32) + sizeof(dataId_t) + sizeof(value);
    outStream.device()->seek(0);
    outStream << size;
}

template<typename T>
inline void Command<T>::update(const T &value)
{
    if (progress == commandProgress_t::kInProgress
        && value == this->value)
    {
        progress = commandProgress_t::kSuccess;
    }
}

template<typename T>
inline bool Command<T>::inProgess()
{
    return progress == commandProgress_t::kInProgress;
}

#endif //  COMMAND_H_
