#ifndef ROBOTSIM__DATAVEC_H
#define ROBOTSIM__DATAVEC_H

#include <array>
#include <inttypes.h>
#include "DataCommon.h"

/**
 * Represents a readable 32bit integer array data of the robot simulator.
 */
template <size_t n>
class DataVecInt
{
public:
    DataVecInt(const dataId_t id,
               const int32_t minVal,
               const int32_t maxVal,
               const int32_t init);

    void    update(const bool estop);
    void    write(const bool needSync);

private:
    const dataId_t  dataId;
    const int32_t   minValue;
    const int32_t   maxValue;
    std::array<int32_t, n>  actual;
    std::array<int32_t, n>  lastSent;
    std::array<int32_t, n>  goal;
    bool            hasCmd;
};

/**
 * Represents a readable 64bit floating point array data of the robot
 * simulator.
 */
template <size_t n>
class DataVecDouble
{
public:
    DataVecDouble(const dataId_t id,
                  const double minVal,
                  const double maxVal,
                  const double init,
                  const double maxDiff);

    void    update(const bool estop);
    void    write(const bool needSync);

private:
    const dataId_t  dataId;
    const double    minValue;
    const double    maxValue;
    const double    maxDiff;
    std::array<double, n>   actual;
    std::array<double, n>   lastSent;
    std::array<double, n>   goal;
    bool            hasCmd;
};

#endif // !ROBOTSIM__DATAVEC_H

