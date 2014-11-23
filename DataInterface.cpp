#include "DataInterface.h"

QDataStream & operator >>(QDataStream &inStream, dataId_t &dataId)
{
    inStream >> (quint32&)dataId;
    return inStream;
}

std::string getDataIdStr(const dataId_t &dataId)
{
    switch (dataId) {
    case kD_Sync:
        return "Synchronization";
        break;
    case kD_Estop:
        return "Emergency stop";
        break;
    case kD_Velocity:
        return "Velocity";
        break;
    case kD_Accel:
        return "Acceleration";
        break;
    case kD_SteerAng:
        return "Steering angle";
        break;
    case kD_LightSen:
        return "Light sensor";
        break;
    case kD_DistSen:
        return "Distance sensor";
        break;
    case kD_SmState:
        return "State machine";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}

DataInterface::~DataInterface()
{
}
