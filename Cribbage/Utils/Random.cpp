#include "Random.h"

#include <stdlib.h>
#include <chrono>
#include <sys/time.h>
#include <ctime>
#include <iostream>

using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::seconds;
using std::chrono::high_resolution_clock;

Random* Random::sSingleton = NULL;

Random* Random::Instance()
{
    if (sSingleton == NULL)
    {
        sSingleton = new Random();
    }

    return sSingleton;
}

Random::Random()
{
    auto seed = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
    srand(seed);

    sSingleton = this;
}

Random::~Random()
{
    sSingleton = NULL;
}

int Random::randInt(int modulo)
{
    if (modulo == -1) { return rand(); }
    else { return rand() % modulo; }
}
