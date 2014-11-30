#include "RobotSim.h"
#include <algorithm>
#include <assert.h>
#include <math.h>

const int RobotSim::kUpdateDiffMs = 50;
const int RobotSim::kSendDiffMs = 100;

RobotSim::RobotSim()
 : needSync(false),
   estop(false),
   state(kD_SmState, 0, 8, 0),
   velocity(kD_Velocity, -8.0, 10.0, 0.0, 0.2),
   acceleration(kD_Accel, -3.0, 5.0, 0.0, 0.1),
   steerAngle(kD_SteerAng, -65.0, 65.0, 0.0, 2.5),
   ctlSignal(kD_CtlSignal, -100.0, 100.0, 0.0, 20.0)
{
    lastUpdate = QDateTime::currentDateTime();
    lastSend = lastUpdate;
}

void RobotSim::Do_a_Step()
{
    if (socket.hasNoConn()) accept();
    receive();

    QDateTime actual = QDateTime::currentDateTime();
    qint64 updDiffMs = lastUpdate.msecsTo(actual);
    qint64 sendDiffMs = lastSend.msecsTo(actual);

    if (updDiffMs >= _MyT::kUpdateDiffMs)
    {
        update();
        lastUpdate = actual;
    }
    if (sendDiffMs >= _MyT::kSendDiffMs)
    {
        send();
        lastSend = actual;
    }
}

void RobotSim::update()
{
    state.update(estop);
    velocity.update(estop);
    acceleration.update(estop);
    ctlSigna.update(estop);
    steerAngl.update(estop);
    distSensor.update(estop);
    lightSensor(estop);
}

void RobotSim::send()
{
    state.write(needSync);
    velocity.write(needSync);
    acceleration.write(needSync);
    steerAngle.write(needSync);
    distSensor.write(needSync);
    lightSensor.write(needSync);
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
        velocity.setEstop();
        acceleration.setEstop();
        steerAngle.setEstop();
        ctlSignal.setEstop();
        break;
    case kD_Velocity:
        estop = false;
        velocity.read();
        break;
    case kD_Accel:
        estop = false;
        acceleration.read();
        break;
    case kD_SteerAng:
        estop = false;
        steerAngle.read();
        break;
    case kD_SmState:
        estop = false;
        state.read();
        break;
    default:
        assert(0 && "Unknown data id received.");
        break;
    }
}

