#include "RobotSim.h"

int main(int argc, char **argv)
{
    RobotSim r;
    while (true)
    {
        r.Do_a_Step();
        sleep(50);
    }
    return 0;
}

