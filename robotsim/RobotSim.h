#ifndef ROBOTSIM__ROBOTSIM_H
#define ROBOTSIM__ROBOTSIM_H

#include <inttypes.h>
#include <vector>
#include <QDateTime>
#include "Data.h"

#define ROB_STA_ACTUAL      0   // Actual state value.
#define ROB_STA_LASTSENT    1   // Last sent value of state.
#define ROB_STA_MINVAL      2   // Minimum allowed value.
#define ROB_STA_MAXVAL      3   // Maximum allowed value.
#define ROB_STA_GOAL        4   // Goal value of state (optional).
// State sizes.
#define ROB_STA_WRITE_SIZE  4
#define ROB_STA_RW_SIZE     5

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

    static const int kUpdateDiffMs;
    static const int kSendDiffMs;

    void        update();
    void        send();
    void        receive();

    void        resetDataVec(std::vector<int32_t> *w_data,
                             const size_t n,
                             const int32_t value);
    void        resetDataVec(std::vector<double> *w_data,
                             const size_t n,
                             const double value);
    void        processRecvData(const char *buffer);

    QDateTime   lastUpdate;
    QDateTime   lastSend;

    bool        needSync;
    bool        estop;

    DataInt     state;
    DataDouble  velocity;
    DataDouble  acceleration;
    DataDouble  steerAngle;
    DataDouble  ctlSignal;
    std::vector< double >   distSensor[ROB_STA_WRITE_SIZE];
    std::vector< int32_t >  lightSensor[ROB_STA_WRITE_SIZE];

    socket      socket;
};

#endif // !ROBOTSIM__ROBOTSIM_H

