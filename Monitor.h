#ifndef MONITOR_H_
#define MONITOR_H_

#include <QObject>

#include "DataContainer.h"
#include "Network.h"

class Monitor : public QObject
{
    Q_OBJECT

public:

    void receive();
    void send(const dataId_t dataId);

public slots:
    void sync();
    void emergencyStop();

private:
    DataContainer dataContainer;
    Network network;

};
#endif // MONITOR_H_
