#ifndef DATA_STATE_ONLY_H_
#define DATA_STATE_ONLY_H_

#include <QDataStream>

#include "DataInterface.h"
#include "QCircularBuffer.h"
#include "State.h"

template<typename T>
class DataStateOnly : public DataInterface
{

public:
    QCircularBuffer< State<T> > states;

    virtual void sendCommand(QDataStream &outStream,
                             const bool onlyInProgress = false) override;
    virtual void deserialise(QDataStream &inStream) override;
    virtual void updateCommand() override;

};
#endif // DATA_STATE_ONLY_H_
