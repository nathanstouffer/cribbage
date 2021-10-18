#include "RandomPeggerAI.h"

#include "PeggerAI.h"
#include "../../Utils/Random.h"
#include "../../Utils/Card.h"
#include "../../Utils/Hand.h"

RandomPeggerAI::~RandomPeggerAI() {}

Card RandomPeggerAI::select(const std::vector<Card>& played, const std::vector<Card>& avail)
{
    std::vector<Card> validCards = PeggerAI::valid(played, avail);
    if (validCards.size() == 0) { return Card(); }

    int i = Random::Instance()->randInt() % validCards.size();
    return validCards[i];
}
