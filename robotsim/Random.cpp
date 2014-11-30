#include "Random.h"
#include <stdlib.h>

void Random::init(const unsigned int seed)
{
    srand(seed);
}

int32_t Random::getRand(const int32_t min, const int32_t max)
{
    //return min + rand() % ((max + 1) - min);
    return min
           + static_cast<int32_t>((rand() / (double)RAND_MAX) * (max - min));
}

double Random::getRand(const double min, const double max)
{
    return min + (rand() / (double)RAND_MAX) * (max - min);
}

