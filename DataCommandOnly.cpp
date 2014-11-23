#include "DataCommandOnly.h"

template <typename T>
void DataCommandOnly<T>::sendCommand(const ValueWrapper &value,
                                     QDataStream &outStream,
                                     const bool onlyInProgress)
{
    if (!onlyInProgress || command.inProgess())
    {
        command.serialise(value, outStream);
    }
}

template <typename T>
void DataCommandOnly<T>::deserialise(QDataStream &)
{
    // No states, nothing to do.
}

template <typename T>
void DataCommandOnly<T>::updateCommand()
{
    // No states, nothing to update with.
}
