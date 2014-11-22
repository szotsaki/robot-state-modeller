#ifndef DATA_INTERFACE_H_
#define DATA_INTERFACE_H_

#include <QDataStream>

#include "State.h"

class DataInterface
{

    virtual void sendCommand(QDataStream& stream, bool onlyInProgress = false) = 0;
    virtual void deserialise(QDataStream& stream) = 0;
    virtual void updateCommand() = 0;

};
#endif // DATA_INTERFACE_H_
