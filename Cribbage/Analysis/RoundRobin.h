#ifndef __ROUND_ROBIN_H__
#define __ROUND_ROBIN_H__

#include <string>
#include <array>

#include "../AIs/Hand/HandAI.h"
#include "../AIs/Pegger/PeggerAI.h"

struct RoundRobin
{

    RoundRobin(std::string inFileName);

    void run();

    void setOutputFileName();

private:

    std::string mInFileName;
    std::string mOutFileName;
    std::string mOutputString;
    int mNumGames;

    std::vector<HandAIEnum> mHandStrategies;
    std::vector<PeggerAIEnum> mPeggerStrategies;

    void battle(int i, int j);

};

#endif
