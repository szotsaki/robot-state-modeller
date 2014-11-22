#ifndef DATA_STATE_ONLY_H_
#define DATA_STATE_ONLY_H_

#include <QDataStream>

#include "DataInterface.h"
#include "State.h"

template<typename T>
class DataStateOnly : public DataInterface
{

public:
    State<T> state;

    virtual void sendCommand(QDataStream& stream, bool onlyInProgress = false) override;
    virtual void deserialise(QDataStream& stream) override;
    virtual void updateCommand(State<T>& state) override;

};
#endif // DATA_STATE_ONLY_H_
