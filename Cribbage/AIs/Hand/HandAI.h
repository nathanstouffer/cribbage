#ifndef __HANDAI_H__
#define __HANDAI_H__

#include <vector>
#include <string>
#include "../../Utils/Card.h"

#define CUT_PROB 1.0/46.0               // probability that a given card is cut
#define THROW_PROB 2.0/(45.0*44.0)      // probability that the two cards are thrown into the crib

#define SIX_CHOOSE_TWO 15               // value of 6 choose 2

enum HandAIEnum
{
    RandomH, RetainedEVH, GrossHalfCribEVH, RelativeHalfCribEVH, GrossFullCribEVH, RelativeFullCribEVH
};

class HandAI
{
public:

    virtual ~HandAI() {}

    // returns the four selected cards in a vector
    virtual std::vector<Card> select(const std::vector<Card>& dealt, bool isMyCrib) = 0;

    static std::string enumToString(HandAIEnum handAIType);

    static HandAIEnum stringToEnum(std::string str);
};

#endif
