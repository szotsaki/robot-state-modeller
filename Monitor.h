#ifndef MONITOR_H_
#define MONITOR_H_

#include "DataContainer.h"
#include "Network.h"

class Monitor
{

public:

    void receive();
    void send(const dataId_t dataId);
    void sync();

private:
    DataContainer dataContainer;
    Network network;

};
#endif // MONITOR_H_
