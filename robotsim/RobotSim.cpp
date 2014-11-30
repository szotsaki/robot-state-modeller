#include "RobotSim.h"
#include <assert.h>
#include <math.h>

typedef enum
{
    kD_Sync = 0,
    kD_Estop,
    kD_Velocity,
    kD_Accel,
    kD_SteerAng,
    kD_LightSen,
    kD_DistSen,
    kD_SmState
} dataId_t;

RobotSim::RobotSim()
 : needSync(false),
   estop(false),
   stateHasCmd(false),
   velocityHasCmd(false),
   accelerationHasCmd(false),
   steerAngleHasCmd(false),
   ctlSignalHasCmd(false)
{
    Timestamp actual;
    getActualTime(actual);
    lastUpdate = actual;
    lastSend = actual;

    // Reset states.
    resetData(state, 0);
    resetData(velocity, 0.0);
    resetData(acceleration, 0.0);
    resetData(steerAngle, 0.0);
    resetData(ctlSignal, 0.0);
    resetDataVec(distSensor, 3, 0.0);
    resetDataVec(lightSensor, 8, 0);
}

void RobotSim::Do_a_Step()
{
    if (socket.hasNoConn()) accept();
    receive();

    Timestamp actual;
    getActualTime(actual);
    int updDiff = actual - lastUpdate;
    int sendDiff = actual - lastSend;

    if (updDiff >= kUpdateDiff)
    {
        update();
        lastUpdate = actual;
    }
    if (sendDiff >= kSendDiff)
    {
        send();
        lastSend = actual;
    }
}

void RobotSim::update()
{
    updateData(state, stateHasCmd);
    updateData(velocity, velocityHasCmd);
    updateData(acceleration, accelerationHasCmd);
    updateData(ctlSignal, ctlSignalHasCmd);
    updateData(steerAngle, steerAngleHasCmd);
    updateDataVec(distSensor);
    updateDataVec(lightSensor);
}

void RobotSim::send()
{
    writeData(state);
    writeData(velocity);
    writeData(acceleration);
    writeData(steerAngle);
    writeDataVec(distSensor);
    writeDataVec(lightSensor);
    if (!buffer.empty())
    {
        send(buffer);
    }
    needSync = false;
}

void RobotSim::receive()
{
    int recvCount = 5;
    while (recvCount && hasPendingBytes)
    {
        // Actual receive logic.
        int nextCmdSize = peekInteger(); // Peek only, do not read.
        if (pendingBytes < nextCmdSize)
        {
            break;
        }
        readInteger();
        buffer = readBytes(nextCmdSize);
        processRecvData(buffer);
        --recvCount;
    }
}

void RobotSim::resetData(int32_t *rw_data, const int32_t value)
{
    rw_data[ROB_STA_ACTUAL] = rw_data[ROB_STA_LASTSENT]
                              = rw_data[ROB_STA_GOAL] = value;
}

void RobotSim::resetData(double *rw_data, const double value)
{
    rw_data[ROB_STA_ACTUAL] = rw_data[ROB_STA_LASTSENT]
                              = rw_data[ROB_STA_GOAL] = value;
}

void RobotSim::resetDataVec(std::vector<int32_t> *w_data,
                            const size_t n,
                            const int32_t value)
{
    w_data[ROB_STA_ACTUAL].resize(n);
    w_data[ROB_STA_LASTSENT].resize(n);
    for (size_t i = 0; i < n; ++i)
    {
        w_data[ROB_STA_ACTUAL][i] = w_data[ROB_STA_LASTSENT][i] = value;
    }
}

void RobotSim::resetDataVec(std::vector<double> *w_data,
                            const size_t n,
                            const double value)
{
    w_data[ROB_STA_ACTUAL].resize(n);
    w_data[ROB_STA_LASTSENT].resize(n);
    for (size_t i = 0; i < n; ++i)
    {
        w_data[ROB_STA_ACTUAL][i] = w_data[ROB_STA_LASTSENT][i] = value;
    }
}

void RobotSim::updateData(int32_t *rw_data, bool &hasCmd)
{
    if (!hasCmd && !estop && rand(ROB_RP_CHANGE_GOAL) == 0)
    {
        rw_data[ROB_STA_GOAL] = rand(min, max);
    }
    if (rw_data[ROB_STA_ACTUAL] != rw_data[ROB_STA_GOAL])
    {
        rw_data[ROB_STA_ACTUAL] = rw_data[ROB_STA_GOAL];
        hasCmd = false;
    }
}

void RobotSim::updateData(double *rw_data, bool &hasCmd)
{
    if (!hasCmd && !estop && rand(ROB_RP_CHANGE_GOAL) == 0)
    {
        rw_data[ROB_STA_GOAL] = rand(min, max);
    }
    if (rw_data[ROB_STA_ACTUAL] != rw_data[ROB_STA_GOAL])
    {
        double diff = (rw_data[ROB_STA_GOAL] - rw_data[ROB_STA_GOAL]) * 0.8;
        diff = clampMaxAbs(diff, kMaxDiff);
        rw_data[ROB_STA_ACTUAL] += diff;

        if (hasCmd && rw_data[ROB_STA_ACTUAL] == rw_data[ROB_STA_GOAL])
        {
            hasCmd = false;
        }
    }
}

void RobotSim::writeData(int32_t *rw_data)
{
    if (rw_data[ROB_STA_ACTUAL] != rw_data[ROB_STA_LASTSENT]
        || needSync)
    {
        int size = 12;
        writeInteger(size);
        writeInteger(type);
        writeInteger(rw_data[ROB_STA_ACTUAL]);
        rw_data[ROB_STA_LASTSENT] = rw_data[ROB_STA_ACTUAL];
    }
}

void RobotSim::writeData(double *rw_data)
{
    if (rw_data[ROB_STA_ACTUAL] != rw_data[ROB_STA_LASTSENT]
        || needSync)
    {
        int size = 16;
        writeInteger(size);
        writeInteger(type);
        writeDouble(rw_data[ROB_STA_ACTUAL]);
        rw_data[ROB_STA_LASTSENT] = rw_data[ROB_STA_ACTUAL];
    }
}

void RobotSim::processRecvData(const char *buffer)
{
    int32_t type = readInteger();
    switch (type)
    {
    case kD_Sync:
        needSync = true;
        break;
    case kD_Estop:
        estop = true;
        velocity[ROB_STA_GOAL] = 0.0;
        acceleration[ROB_STA_GOAL] = 0.0;
        steerAngle[ROB_STA_GOAL] = 0.0;
        ctlSignal[ROB_STA_GOAL] = 0.0;
        break;
    case kD_Velocity:
        estop = false;
        velocity[ROB_STA_GOAL] = readDouble();
        velocityHasCmd = true;
        break;
    case kD_Accel:
        estop = false;
        acceleration[ROB_STA_GOAL] = readDouble();
        accelerationHasCmd = true;
        break;
    case kD_SteerAng:
        estop = false;
        steerAngle[ROB_STA_GOAL] = readDouble();
        steerAngleHasCmd = true;
        break;
    case kD_SmState:
        estop = false;
        state[ROB_STA_GOAL] = readInteger();
        stateHasCmd = true;
        break;
    default:
        assert(0 && "Unknown data id received.");
        break;
    }
}

double RobotSim::clampMaxAbs(const double d, const double dMaxAbs)
{
    double res = d;
    if (abs(d) > dMaxAbs)
    {
        res *= dMaxAbs / abs(d);
    }
    return res;
}

double RobotSim::clamp(const double d, const double dMin, const double dMax)
{
    return min(dMax, max(dMin, d));
}

