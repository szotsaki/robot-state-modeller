#include "DataStateOnly.h"

template <typename T>
void DataStateOnly<T>::sendCommand(QDataStream &, const bool)
{
    // Has no command, nothing to do.
}

template <typename T>
void DataStateOnly<T>::deserialise(QDataStream &inStream)
{
    State<T> s;
    s.deserialise(inStream);
    states.push_back(s);
}

template <typename T>
void DataStateOnly<T>::updateCommand()
{
    // Has no command, nothing update.
}
