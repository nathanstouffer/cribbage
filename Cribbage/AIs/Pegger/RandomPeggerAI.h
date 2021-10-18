#ifndef __RANDOMPEGGERAI_H__
#define __RANDOMPEGGERAI_H__

#include "PeggerAI.h"
#include "../../Utils/Card.h"

class RandomPeggerAI : public PeggerAI
{
public:
    ~RandomPeggerAI();

    Card select(const std::vector<Card>& played, const std::vector<Card>& avail);

};

#endif
