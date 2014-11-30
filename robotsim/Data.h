#ifndef ROBOTSIM__DATA_H
#define ROBOTSIM__DATA_H

#include <inttypes.h>
#include "DataCommon.h"

/**
 * Represents a readable+writable 32bit integer data of the robot simulator.
 */
class DataInt
{
public:
    DataInt(const dataId_t id,
            const int32_t minVal,
            const int32_t maxVal,
            const int32_t init);

    void    update(const bool estop);
    void    write(const bool needSync);
    void    read();

private:
    const dataId_t  dataId;
    const int32_t   minValue;
    const int32_t   maxValue;
    int32_t         actual;
    int32_t         lastSent;
    int32_t         goal;
    bool            hasCmd;
};

/**
 * Represents a readable+writable 64bit floating point data of the robot
 * simulator.
 */
class DataDouble
{
public:
    DataDouble(const dataId_t id,
               const double minVal,
               const double maxVal,
               const double init,
               const double maxDiff);

    void    update(const bool estop);
    void    write(const bool needSync);
    void    read();
    void    setEstop();

private:
    const dataId_t  dataId;
    const double    minValue;
    const double    maxValue;
    const double    maxDiff;
    double          actual;
    double          lastSent;
    double          goal;
    bool            hasCmd;
};

#endif // !ROBOTSIM__DATA_H

