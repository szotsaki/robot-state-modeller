#ifndef MONITOR_H_
#define MONITOR_H_

#include "DataContainer.h"
#include "Network.h"
#include "Command.h"

class Monitor
{

public:
    DataContainer dataContainer;
    Network network;

	void receive();
    void send(int ID);
	void sync();

};
#endif // MONITOR_H_
