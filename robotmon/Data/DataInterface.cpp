#include "DataInterface.h"

dataValueType_t dataValueTypes[kD_NumIds] =
{
    kDvt_Int32,
    kDvt_Int32,
    kDvt_Float64,
    kDvt_Float64,
    kDvt_Float64,
    kDvt_Int32Vec,
    kDvt_Float64Vec,
    kDvt_Int32
};

std::string dataIdTexts[kD_NumIds] =
{
    "Synchronization",
    "Emergency stop",
    "Velocity",
    "Acceleration",
    "Steering angle",
    "Light sensor",
    "Distance sensor",
    "State machine"
};

QDataStream & operator >>(QDataStream &inStream, dataId_t &dataId)
{
    inStream >> (quint32&)dataId;
    return inStream;
}

DataInterface::~DataInterface()
{
}
