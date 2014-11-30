#ifndef ROBOTSIM__ROBOTSIM_H
#define ROBOTSIM__ROBOTSIM_H

#include <inttypes.h>
#include <vector>
#include <QDateTime>
#include "Data.h"
#include "DataVec.h"

/**
 * Simulator of an actual robot for testing purposes.
 * Handles network connection and data simulation on its own.
 */
class RobotSim
{
public:
    RobotSim();

    void        Do_a_Step();

private:
    typedef RobotSim    _MyT;

    static const int    kUpdateDiffMs;
    static const int    kSendDiffMs;

    void                update();
    void                send();
    void                receive();

    void                resetDataVec(std::vector<int32_t> *w_data,
                                     const size_t n,
                                     const int32_t value);
    void                resetDataVec(std::vector<double> *w_data,
                                     const size_t n,
                                     const double value);
    void                processRecvData(const char *buffer);

    QDateTime           lastUpdate;
    QDateTime           lastSend;

    bool                needSync;
    bool                estop;

    DataInt             state;
    DataDouble          velocity;
    DataDouble          acceleration;
    DataDouble          steerAngle;
    DataDouble          ctlSignal;
    DataVecDouble<3>    distSensor;
    DataVecInt<8>       lightSensor;

    socket              socket;
};

#endif // !ROBOTSIM__ROBOTSIM_H

