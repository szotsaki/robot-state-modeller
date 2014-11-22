#include "Data.h"

template<typename T>
void Data<T>::sendCommand(QDataStream &outStream,
                          const bool onlyInProgress)
{
    if (!onlyInProgress || command.inProgess())
    {
        command.serialise(outStream);
    }
}

template<typename T>
void Data<T>::deserialise(QDataStream &inStream)
{
    State<T> s;
    s.deserialise(inStream);
    states.push_back(s);
}

template<typename T>
void Data<T>::updateCommand()
{
    const T value = states.at(0).getValue();
    command.update(value);
}
