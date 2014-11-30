#ifndef ROBOTSIM__RANDOM_H
#define ROBOTSIM__RANDOM_H

#include <stdint.h>

class Random
{
public:
    static void     init(const unsigned int seed);
    static int32_t  getRand(const int32_t min, const int32_t max);
    static double   getRand(const double min, const double max);
};

#endif // !ROBOTSIM__RANDOM_H

