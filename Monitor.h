#ifndef MONITOR_H_
#define MONITOR_H_

#include <QObject>

#include "DataContainer.h"
#include "Network.h"
#include "Command.h"

class Monitor : public QObject
{
    Q_OBJECT

public:
    DataContainer dataContainer;
    Network network;

	void receive();
    void send(int ID);

public slots:
    void sync();
    void emergencyStop();

};
#endif // MONITOR_H_
