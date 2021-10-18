#include "Player.h"

#include "../AIs/Hand/RandomHandAI.h"
#include "../AIs/Hand/RetainedEVHandAI.h"
#include "../AIs/Hand/GrossHalfCribEVHandAI.h"
#include "../AIs/Hand/RelativeHalfCribEVHandAI.h"
#include "../AIs/Hand/GrossFullCribEVHandAI.h"
#include "../AIs/Hand/RelativeFullCribEVHandAI.h"

#include "../AIs/Pegger/RandomPeggerAI.h"
#include "../AIs/Pegger/HeuristicPeggerAI.h"

Player::Player(HandAIEnum handAIType, PeggerAIEnum peggerAIType)
{
    setHandAI(handAIType);
    setPeggerAI(peggerAIType);
}

Player::~Player()
{
    if (mHandAI != NULL)   { delete mHandAI; }
    if (mPeggerAI != NULL) { delete mPeggerAI; }
    mNotPegged.clear();
    mPegged.clear();
}

void Player::markPegged(const Card& card)
{
    int i = -1;
    for (int n = 0; n < mNotPegged.size(); n++)
    {
        if (mNotPegged[n] == card) { i = n; }
    }

    if (i == -1) { std::cerr << "Card not in vector" << std::endl; }
    else
    {
        mPegged.push_back(mNotPegged[i]);
        mNotPegged.erase(mNotPegged.begin()+i);
    }
}

void Player::setHandAI(HandAIEnum handAIType)
{
    if (mHandAI != NULL) { delete mHandAI; }
    mHandAIType = handAIType;
    switch (handAIType)
    {
        case HandAIEnum::RandomH:               mHandAI = new RandomHandAI();               break;
        case HandAIEnum::RetainedEVH:           mHandAI = new RetainedEVHandAI();           break;
        case HandAIEnum::GrossHalfCribEVH:      mHandAI = new GrossHalfCribEVHandAI();      break;
        case HandAIEnum::RelativeHalfCribEVH:   mHandAI = new RelativeHalfCribEVHandAI();   break;
        case HandAIEnum::GrossFullCribEVH:      mHandAI = new GrossFullCribEVHandAI();      break;
        case HandAIEnum::RelativeFullCribEVH:   mHandAI = new RelativeFullCribEVHandAI();   break;
        default:                                mHandAI = NULL;
    }
}

void Player::setPeggerAI(PeggerAIEnum peggerAIType)
{
    if (mPeggerAI != NULL) { delete mPeggerAI; }
    mPeggerAIType = peggerAIType;
    switch (peggerAIType)
    {
        case PeggerAIEnum::RandomP:     mPeggerAI = new RandomPeggerAI();       break;
        case PeggerAIEnum::HeuristicP:  mPeggerAI = new HeuristicPeggerAI();    break;
        defualt:                        mPeggerAI = NULL;
    }
}
