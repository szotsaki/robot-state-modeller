#ifndef ROBOTSIM__DATACOMMON_H
#define ROBOTSIM__DATACOMMON_H

#include <algorithm>

typedef enum
{
    kD_Sync = 0,
    kD_Estop,
    kD_Velocity,
    kD_Accel,
    kD_SteerAng,
    kD_LightSen,
    kD_DistSen,
    kD_SmState,
    kD_CtlSignal
} dataId_t;

template <typename T>
T clamp(const T v, const T vMin, const T vMax);

template <typename T>
T clampMaxAbs(const T v, const T vMax);

template <typename T>
inline T clamp(const T v, const T vMin, const T vMax)
{
    return std::min(vMax, std::max(vMin, v));
}

template <typename T>
inline T clampMaxAbs(const T v, const T vMaxAbs)
{
    double res = v;
    if (abs(v) > vMaxAbs)
    {
        res *= vMaxAbs / abs(v);
    }
    return res;
}

#endif // !ROBOTSIM__DATACOMMON_H

