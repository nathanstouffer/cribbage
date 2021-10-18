#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>

#include "../AIs/Hand/HandAI.h"
#include "../AIs/Pegger/PeggerAI.h"
#include "../Utils/Card.h"

struct Score
{
private:
    int mValue;

public:

    Score() : mValue(0) {}
    Score(int value) : mValue(value) {}

    Score operator=(int amount)
    {
        if (amount > 121)
        {
            std::cout << "ERROR: value is greater than 121" << std::endl;
        }
        return Score(amount);
    }

    Score operator+(int amount)
    {
        if (mValue > 120)
        {
            std::cout << "ERROR: score is already above 120" << std::endl;
            return *this;
        }
        else
        {
            return Score(std::min(121, mValue + amount));
        }
    }

    void operator+=(int amount)
    {
        if (mValue > 120)
        {
            std::cout << "ERROR: score is already above 120" << std::endl;
        }
        else
        {
            mValue += amount;
            mValue = std::min(121, mValue);
        }
    }

    bool operator>(const Score& oth) { return mValue > oth.getValue(); }
    bool operator<(const Score& oth) { return mValue < oth.getValue(); }

    bool operator>(int comp) { return mValue > comp; }
    bool operator<(int comp) { return mValue < comp; }

    int getValue() const { return mValue; }

};

struct Player
{
    HandAIEnum mHandAIType;
    PeggerAIEnum mPeggerAIType;

    HandAI* mHandAI = NULL;
    PeggerAI* mPeggerAI = NULL;

    Score mScore;

    std::vector<Card> mNotPegged;
    std::vector<Card> mPegged;

    Player(HandAIEnum handAIType, PeggerAIEnum peggerAIType);
    ~Player();

    void markPegged(const Card& card);

    void setHandAI(HandAIEnum handAIType);
    void setPeggerAI(PeggerAIEnum peggerAIType);
};

#endif
