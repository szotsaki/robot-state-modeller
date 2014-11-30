#include "RobotSim.h"
#include "Sleep.h"

int main(int argc, char **argv)
{
    RobotSim r;
    while (true)
    {
        r.Do_a_Step();
        r_sleepMs(50);
    }
    return 0;
}

