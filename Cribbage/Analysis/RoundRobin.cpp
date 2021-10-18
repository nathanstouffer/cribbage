#include "RoundRobin.h"

#include "../Game/Game.h"
#include "../Game/Player.h"
#include "../AIs/Hand/HandAI.h"
#include "../AIs/Pegger/PeggerAI.h"

#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>


RoundRobin::RoundRobin(std::string inFileName) :
      mInFileName(inFileName)
{
    setOutputFileName();
    std::string line;
    std::ifstream fin(mInFileName);
    if (fin.is_open())
    {
        if (std::getline(fin, line))                    // read meta data from first line
        {
            size_t commaPos = line.find(",");
            line.erase(0, commaPos + 1);                // add one to also get rid of the comma
            mNumGames = std::stoi(line);
        }
        while (std::getline(fin, line))                 // read in the strategies
        {
            size_t commaPos = line.find(",");
            std::string handAI = line.substr(0, commaPos);
            line.erase(0, commaPos + 1);                // add one to also get rid of the comma
            std::string peggAI = line;

            mHandStrategies.push_back(HandAI::stringToEnum(handAI));
            mPeggerStrategies.push_back(PeggerAI::stringToEnum(peggAI));
        }
        fin.close();
    }

    mOutputString = HandAI::enumToString(mHandStrategies[0]) + "-" + PeggerAI::enumToString(mPeggerStrategies[0]);
    for (int s = 1; s < mHandStrategies.size(); s++)
    {
        mOutputString += "," + HandAI::enumToString(mHandStrategies[s]) + "-" + PeggerAI::enumToString(mPeggerStrategies[s]);
    }
    mOutputString += "\nNUM_GAMES," + std::to_string(mNumGames);
    mOutputString += "\nstrat1,strat1WinPerc,strat1AvgPtDiff,strat2,strat2WinPerc,strat2AvgPtDiff";
}

void RoundRobin::run()
{
    std::string dashes = "------------------------------------------------------------------------";
    std::cout << "beg round robin " << dashes << std::endl;

    int numStrats = mHandStrategies.size();
    std::cout << "  we have " << numStrats * (numStrats + 1) / 2 << " match-ups, ";
    std::cout << "each match-up consists of " << mNumGames << " games" << std::endl;

    time_t start = std::time(NULL);
    int count = 0;
    for (int i = 0; i < numStrats; i++)
    {
        for (int j = i; j < numStrats; j++)
        {
            char info[2048];
            std::string p1 = HandAI::enumToString(mHandStrategies[i]) + "-" + PeggerAI::enumToString(mPeggerStrategies[i]);
            std::string p2 = HandAI::enumToString(mHandStrategies[j]) + "-" + PeggerAI::enumToString(mPeggerStrategies[j]);
            sprintf(info, "  round %-4d: %-30s vs %-30s", ++count, p1.c_str(), p2.c_str());
            std::cout << std::string(info) << std::flush;
            time_t roundStart = std::time(NULL);
            battle(i, j);
            time_t current = std::time(NULL);                                   // get current time
            std::cout << "   " << current-roundStart << " s" << std::endl;
        }
    }

    time_t current = std::time(NULL);
    std::cout << "  total time: " << current-start << " s" << std::endl;
    std::cout << "end round robin " << dashes << std::endl;

    std::ofstream fout(mOutFileName);
    fout << mOutputString;
    fout.close();
}

void RoundRobin::battle(int i, int j)
{
    Player playerA(mHandStrategies[i], mPeggerStrategies[i]);
    Player playerB(mHandStrategies[j], mPeggerStrategies[j]);

    int aWins = 0, bWins = 0;
    float aAvgPtDiff = 0.0, bAvgPtDiff = 0.0;               // when player k wins, on average how many points do they win by?
    for (int i = 0; i < mNumGames; i++)
    {
        Game* game;
        if (i % 2 == 0) { game = new Game(playerA, playerB); }
        if (i % 2 == 1) { game = new Game(playerB, playerA); }

        game->play();
        Winner winner = game->winner();

        if (i % 2 == 0)
        {
            if (winner == Winner::FirstPlayer)  { aWins++; aAvgPtDiff += 121 - game->mP2.mScore.getValue(); }
            if (winner == Winner::SecondPlayer) { bWins++; bAvgPtDiff += 121 - game->mP1.mScore.getValue(); }
        }
        if (i % 2 == 1)
        {
            if (winner == Winner::FirstPlayer)  { bWins++; bAvgPtDiff += 121 - game->mP2.mScore.getValue(); }
            if (winner == Winner::SecondPlayer) { aWins++; aAvgPtDiff += 121 - game->mP1.mScore.getValue(); }
        }

        if (winner == Winner::None)
        {
            std::cerr << "Bad state, nobody won" << std::endl;
        }
        delete game;
    }

    if (aWins > 0) { aAvgPtDiff /= (float)aWins; }        // divide by the number of games won
    if (bWins > 0) { bAvgPtDiff /= (float)bWins; }

    float aWinPerc = (float)aWins / mNumGames;
    float bWinPerc = (float)bWins / mNumGames;

    std::ostringstream info;
    info << std::endl;
    info << HandAI::enumToString(mHandStrategies[i]) << "-" << PeggerAI::enumToString(mPeggerStrategies[i]);
    info << "," << aWinPerc << "," << aAvgPtDiff;
    info << "," << HandAI::enumToString(mHandStrategies[j]) << "-" << PeggerAI::enumToString(mPeggerStrategies[j]);
    info << "," << bWinPerc << "," << bAvgPtDiff;

    mOutputString += info.str();
}

void RoundRobin::setOutputFileName()
{
    size_t extPos = mInFileName.find_last_of(".");
    std::string path = mInFileName.substr(0, extPos);
    size_t whackPos = path.find_last_of("/");
    std::string name = path.substr(whackPos + 1);
    path = path.substr(0, whackPos);
    whackPos = path.find_last_of("/");
    path = path.substr(0, whackPos);
    mOutFileName = path + "/out/" + name + ".out";
}
