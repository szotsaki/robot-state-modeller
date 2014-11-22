#include "State.h"

template<typename T>
void State<T>::deserialise(QDataStream &inStream)
{
    inStream >> value;
    timestamp = QDateTime::currentDateTime();
}

template<typename T>
void State<T>::draw()
{
    // TODO: implement.
}
