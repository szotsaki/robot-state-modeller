#include "Command.h"

template<typename T>
void Command<T>::serialise(const ValueWrapper &wrapper,
                           QDataStream &outStream)
{
    value = static_cast< TValue<T> & >(wrapper).getValue();
    outStream << value;
    progress = commandProgress_t::kInProgress;
}

template<typename T>
void Command<T>::update(const T &value)
{
    if (progress == commandProgress_t::kInProgress
        && value == this->value)
    {
        progress = commandProgress_t::kSuccess;
    }
}

template<typename T>
bool Command<T>::inProgess()
{
    return progress == commandProgress_t::kInProgress;
}
