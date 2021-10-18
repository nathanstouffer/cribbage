#ifndef __RANDOMHANDAI_H__
#define __RANDOMHANDAI_H__

#include <vector>

#include "HandAI.h"
#include "../../Utils/Card.h"

class RandomHandAI : public HandAI
{
public:

    std::vector<Card> select(const std::vector<Card>& dealt, bool isMyCrib);

};

#endif
