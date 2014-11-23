#ifndef DATA_INTERFACE_H_
#define DATA_INTERFACE_H_

#include <QDataStream>
#include <string>
#include "../ValueWrapper.h"

enum dataId_t
{
    kD_Sync = 0,
    kD_Estop,
    kD_Velocity,
    kD_Accel,
    kD_SteerAng,
    kD_LightSen,
    kD_DistSen,
    kD_SmState,
    kD_NumIds
};

QDataStream& operator >>(QDataStream &inStream, dataId_t &dataId);
std::string getDataIdStr(const dataId_t &dataId);

/**
 * The interface for telemetry data.
 * Telemetry data may consists a circular buffer for the most recent N
 * received states, and can also contain a command to modify the value
 * (state) on the robot itself.
 * There can be command only telemetry data (e.g. emergency stop), and
 * state only telemetry data (readings from light sensor).
 */

/**
 * push with Wrapper
 */
class DataInterface
{

public:
    virtual ~DataInterface();

    virtual void sendCommand(const ValueWrapper &value,
                             QDataStream &outStream,
                             const bool onlyInProgress = false) = 0;
    virtual void deserialise(QDataStream &inStream) = 0;
    virtual void updateCommand() = 0;

    virtual std::string getValueText() const = 0;
    virtual void drawTimeChart() const = 0;
    virtual void drawBarChart() const = 0;
};
#endif // DATA_INTERFACE_H_