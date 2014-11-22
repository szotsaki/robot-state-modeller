#include "DataCommandOnly.h"

template <typename T>
void DataCommandOnly<T>::sendCommand(QDataStream &outStream,
                                     const bool onlyInProgress)
{
    if (!onlyInProgress || command.inProgess())
    {
        command.serialise(outStream);
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
