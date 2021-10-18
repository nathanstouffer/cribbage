#ifndef __RETAINED_EV_HAND_AI_H__
#define __RETAINED_EV_HAND_AI_H__

#include <vector>

#include "HandAI.h"
#include "../../Utils/Card.h"

class RetainedEVHandAI : public HandAI
{
public:

    std::vector<Card> select(const std::vector<Card>& dealt, bool isMyCrib);

    float expectedValue(const std::vector<Card>& dealt, const std::vector<Card>& keep);

};

#endif
