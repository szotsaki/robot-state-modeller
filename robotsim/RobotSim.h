#ifndef ROBOTSIM__ROBOTSIM_H
#define ROBOTSIM__ROBOTSIM_H

#include <inttypes.h>
#include <vector>
#include <QDateTime>

#define ROB_STA_ACTUAL      0   // Actual state value.
#define ROB_STA_LASTSENT    1   // Last sent value of state.
#define ROB_STA_GOAL        2   // Goal value of state (optional).
// State sizes.
#define ROB_STA_WRITE_SIZE  2
#define ROB_STA_RW_SIZE     3

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

    void        resetData(int32_t *rw_data, const int32_t value);
    void        resetData(double *rw_data, const double value);
    void        resetDataVec(std::vector<int32_t> *w_data,
                             const size_t n,
                             const int32_t value);
    void        resetDataVec(std::vector<double> *w_data,
                             const size_t n,
                             const double value);
    void        updateData(int32_t *rw_data, bool &hasCmd);
    void        updateData(double *rw_data, bool &hasCmd);
    void        writeData(int32_t *rw_data);
    void        writeData(double *rw_data);
    void        processRecvData(const char *buffer);
    double      clampMaxAbs(const double d, const double dMaxAbs);
    double      clamp(const double d, const double dMin, const double dMax);

    QDateTime   lastUpdate;
    QDateTime   lastSend;

    bool        needSync;
    bool        estop;

    int32_t     state[ROB_STA_RW_SIZE];
    bool        stateHasCmd;
    double      velocity[ROB_STA_RW_SIZE];  // These two fields ..
    bool        velocityHasCmd;             // .. could be in a struct.
    double      acceleration[ROB_STA_RW_SIZE];
    bool        accelerationHasCmd;
    double      steerAngle[ROB_STA_RW_SIZE];
    bool        steerAngleHasCmd;
    double      ctlSignal[ROB_STA_RW_SIZE];
    bool        ctlSignalHasCmd;
    std::vector< double >   distSensor[ROB_STA_WRITE_SIZE];
    std::vector< int32_t >  lightSensor[ROB_STA_WRITE_SIZE];

    socket      socket;
};

#endif // !ROBOTSIM__ROBOTSIM_H

