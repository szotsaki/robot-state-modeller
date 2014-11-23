#ifndef DATA_H_
#define DATA_H_

#include <QDataStream>

#include "Command.h"
#include "DataInterface.h"
#include "QCircularBuffer.h"
#include "State.h"
#include "ValueWrapper.h"

template<typename T>
class Data : public DataInterface
{

public:
    Command<T> command;
    QCircularBuffer< State<T> > states;

    virtual void sendCommand(const ValueWrapper &value,
                             QDataStream &outStream,
                             const bool onlyInProgress = false) override;
    virtual void deserialise(QDataStream &inStream) override;
    virtual void updateCommand() override;

};
#endif // DATA_H_
