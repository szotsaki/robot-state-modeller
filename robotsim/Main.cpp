#include <QTime>
#include "Random.h"
#include "RobotSim.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Random::init((uint)QTime::currentTime().msec());
    RobotSim *r = new RobotSim(&a);

    return a.exec();
}
