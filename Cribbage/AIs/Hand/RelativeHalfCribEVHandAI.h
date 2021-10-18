#ifndef __RELATIVE_HALF_CRIB_EV_HAND_AI_H__
#define __RELATIVE_HALF_CRIB_EV_HAND_AI_H__

#include <vector>

#include "HandAI.h"
#include "../../Utils/Card.h"

class RelativeHalfCribEVHandAI : public HandAI
{
public:

    std::vector<Card> select(const std::vector<Card>& dealt, bool isMyCrib);

    float relativeHalfCribExpectedValue(const std::vector<Card>& toKeep, const std::vector<Card>& toThrow, bool isMyCrib);

    int halfCribScore(const std::vector<Card>& toThrow, const Card& cut);

};

#endif
