#include "Command.h"

template<typename T>
void Command<T>::serialise(QDataStream &outStream)
{
    outStream << value;
    progress = kCp_InProgress;
}

template<typename T>
void Command<T>::update(const T &value)
{
    if (progress == kCp_InProgress
        && value == this->value)
    {
        progress = kCp_Success;
    }
}

template<typename T>
bool Command<T>::inProgess()
{
    return progress == kCp_InProgress;
}
