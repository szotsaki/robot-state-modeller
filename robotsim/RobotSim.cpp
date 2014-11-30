#include "RobotSim.h"

const int RobotSim::kUpdateDiffMs = 50;
const int RobotSim::kSendDiffMs = 100;

RobotSim::RobotSim(QObject *parent)
 : QObject (parent),
   needSync(false),
   estop(false),
   state(kD_SmState, 0, 8, 0),
   velocity(kD_Velocity, -8.0, 10.0, 0.0, 0.2),
   acceleration(kD_Accel, -3.0, 5.0, 0.0, 0.1),
   steerAngle(kD_SteerAng, -65.0, 65.0, 0.0, 2.5),
   ctlSignal(kD_CtlSignal, -100.0, 100.0, 0.0, 20.0),
   distSensor(kD_DistSen, 0.1, 50.0, 25.0, 5.0),
   lightSensor(kD_LightSen, 0, 64, 0),
   clientSocket(nullptr)
{
    lastUpdate = QDateTime::currentDateTime();
    lastSend = lastUpdate;

    socket = new QTcpServer(this);
    if (!socket->listen(QHostAddress::Any, 9999))
    {
        assert(0 || "Cannot open listen socket.");
        qWarning() << "Simulator failed to open socket.";
        qWarning() << socket->errorString();
    }
    else
    {
        qWarning() << "Simulator up and waiting connection.\n";
    }

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &RobotSim::Do_a_Step);
    timer->start(50);
}

void RobotSim::Do_a_Step()
{
    if (!clientSocket)
    {
        clientSocket = socket->nextPendingConnection();
        if (clientSocket) {
            qDebug() << "Monitor connected.\n";
            if (clientSocket->isOpen()) {
                connect(clientSocket, SIGNAL(disconnected()), clientSocket, SLOT(deleteLater()));
            }
        }
    }
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
    ctlSignal.update(estop);
    steerAngle.update(estop);
    distSensor.update(estop);
    lightSensor.update(estop);
}

void RobotSim::send()
{
    if (clientSocket)
    {
        QByteArray buffer;
        QDataStream outStream(&buffer, QIODevice::WriteOnly);

        state.write(outStream, needSync);
        velocity.write(outStream, needSync);
        acceleration.write(outStream, needSync);
        steerAngle.write(outStream, needSync);
        distSensor.write(outStream, needSync);
        lightSensor.write(outStream, needSync);
        if (buffer.size() > 0)
        {
            clientSocket->write(buffer);
        }
        needSync = false;
    }
}

void RobotSim::receive()
{
    if (clientSocket)
    {
        int recvCount = 10;
        QDataStream inStream(clientSocket);
        while (recvCount > 0
               && clientSocket->bytesAvailable() > (int)sizeof(int32_t))
        {
            // Actual receive logic.
            char buffer[4];
            clientSocket->peek(buffer, 4);
            int32_t nextCmdSize = qFromBigEndian<qint32>((uchar *)buffer);
            if (clientSocket->bytesAvailable() < nextCmdSize)
            {
                break;
            }
            inStream >> nextCmdSize;
            processRecvData(inStream);
            --recvCount;
        }
    }
}

void RobotSim::processRecvData(QDataStream &inStream)
{
    int32_t type;
    inStream >> type;
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
        velocity.read(inStream);
        break;
    case kD_Accel:
        estop = false;
        acceleration.read(inStream);
        break;
    case kD_SteerAng:
        estop = false;
        steerAngle.read(inStream);
        break;
    case kD_SmState:
        estop = false;
        state.read(inStream);
        break;
    default:
        Q_ASSERT_X(0, "processRecvData", "Unknown data id received: " + type);
        break;
    }
}

