#ifndef __RELATIVE_FULL_CRIB_EV_HAND_AI_H__
#define __RELATIVE_FULL_CRIB_EV_HAND_AI_H__

#include <vector>
#include <array>

#include "HandAI.h"
#include "../../Utils/Card.h"

class RelativeFullCribEVHandAI : public HandAI
{
public:

    std::array<float, SIX_CHOOSE_TWO> mRelativeEVs;
    std::array<std::vector<Card>, SIX_CHOOSE_TWO> mToKeep;

    std::vector<Card> select(const std::vector<Card>& dealt, bool isMyCrib);

    void setRelativeExpectedValue(int index, const std::vector<Card>& toKeep, const std::vector<Card>& toThrow, bool isMyCrib);

    float relativeExpectedValue(const std::vector<Card>& toKeep, const std::vector<Card>& toThrow, bool isMyCrib);

    float cribExpectedValue(const std::vector<Card>& toKeep, const std::vector<Card>& toThrow, const Card& cut);

};

#endif
