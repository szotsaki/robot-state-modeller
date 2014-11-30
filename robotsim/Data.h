#ifndef ROBOTSIM__DATA_H
#define ROBOTSIM__DATA_H

#include <array>

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
    int32_t clamp(const int32_t d, const int32_t dMin, const int32_t dMax);

    const dataId_t  dataId;
    const int32_t   minValue;
    const int32_t   maxValue;
    int32_t         actual;
    int32_t         lastSent;
    int32_t         goal;
    bool            hasCmd;
};

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

private:
    double  clampMaxAbs(const double d, const double dMaxAbs);
    double  clamp(const double d, const double dMin, const double dMax);

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
