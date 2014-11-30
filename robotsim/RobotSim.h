#ifndef ROBOTSIM__ROBOTSIM_H
#define ROBOTSIM__ROBOTSIM_H

#include <algorithm>
#include <assert.h>
#include <math.h>
#include <QDateTime>
#include <QtCore>
#include <QtNetwork>

#include "Data.h"
#include "DataVec.h"

class QDataStream;
class QTcpServer;
class QTcpSocket;

/**
 * Simulator of an actual robot for testing purposes.
 * Handles network connection and data simulation on its own.
 */
class RobotSim : public QObject
{
    Q_OBJECT

public:
    RobotSim(QObject *parent = 0);


private:
    typedef RobotSim    _MyT;

    static const int    kUpdateDiffMs;
    static const int    kSendDiffMs;

    void        		Do_a_Step();

    void                update();
    void                send();
    void                receive();

    void                processRecvData(QDataStream &inStream);

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

    QTcpServer          *socket;
    QTcpSocket          *clientSocket;
};

#endif // !ROBOTSIM__ROBOTSIM_H
