#include <QTime>
#include "Random.h"
#include "RobotSim.h"
#include "Sleep.h"

int main(int argc, char **argv)
{
    Random::init((uint)QTime::currentTime().msec());

    RobotSim r;
    while (true)
    {
        r.Do_a_Step();
        r_sleepMs(50);
    }
    return 0;
}

