#ifndef DATA_COMMAND_ONLY_H_
#define DATA_COMMAND_ONLY_H_

#include <QDataStream>

#include "Command.h"
#include "DataInterface.h"
#include "State.h"

template<typename T>
class DataCommandOnly : public DataInterface
{

public:
    Command<T> command;

    virtual void sendCommand(QDataStream& stream, bool onlyInProgress = false) override;
    virtual void deserialise(QDataStream& stream) override;
    virtual void updateCommand(State<T>& state) override;

};
#endif // DATA_COMMAND_ONLY_H_
