#ifndef DATA_H_
#define DATA_H_

#include <QDataStream>

#include "Command.h"
#include "DataInterface.h"
#include "State.h"

template<typename T>
class Data : public DataInterface
{

public:
    Command<T> command;
    State<T> state;

    virtual void sendCommand(QDataStream& stream, bool onlyInProgress = false) override;
    virtual void deserialise(QDataStream& stream) override;
    virtual void updateCommand(State<T>& state) override;

};
#endif // DATA_H_
