#ifndef __GROSS_FULL_CRIB_EV_HAND_AI_H__
#define __GROSS_FULL_CRIB_EV_HAND_AI_H__

#include <vector>
#include <array>

#include "HandAI.h"
#include "../../Utils/Card.h"

class GrossFullCribEVHandAI : public HandAI
{
public:

    std::array<float, SIX_CHOOSE_TWO> mGrossEVs;
    std::array<std::vector<Card>, SIX_CHOOSE_TWO> mToKeep;

    std::vector<Card> select(const std::vector<Card>& dealt, bool isMyCrib);

    void setGrossExpectedValue(int index, const std::vector<Card>& toKeep, const std::vector<Card>& toThrow, bool isMyCrib);

    float grossExpectedValue(const std::vector<Card>& toKeep, const std::vector<Card>& toThrow, bool isMyCrib);

    float cribExpectedValue(const std::vector<Card>& toKeep, const std::vector<Card>& toThrow, const Card& cut);

};

#endif
