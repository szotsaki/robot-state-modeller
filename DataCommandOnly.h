#ifndef DATA_COMMAND_ONLY_H_
#define DATA_COMMAND_ONLY_H_

#include <QDataStream>

#include "Command.h"
#include "DataInterface.h"

template<typename T>
class DataCommandOnly : public DataInterface
{

public:
    Command<T> command;

    virtual void sendCommand(QDataStream &outStream,
                             const bool onlyInProgress = false) override;
    virtual void deserialise(QDataStream &inStream) override;
    virtual void updateCommand() override;

};
#endif // DATA_COMMAND_ONLY_H_
