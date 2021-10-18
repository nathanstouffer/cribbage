#include "HeuristicPeggerAI.h"

#include "../../Utils/Card.h"

Card HeuristicPeggerAI::select(const std::vector<Card>& played, const std::vector<Card>& avail)
{
    std::vector<Card> validCards = PeggerAI::valid(played, avail);
    if (validCards.size() == 0) { return Card(); }

    int bestIndx = 0;
    float bestPoints = (float)PeggerAI::points(played, validCards[0]);
    if (PeggerAI::fiveOr21(played, validCards[0])) { bestPoints -= 1.5; }       // sub 1.5 to eliminate checking if there are any downsides
                                                                                // when evaluating ties
    for (int v = 1; v < validCards.size(); v++)
    {
        float points = (float)PeggerAI::points(played, validCards[0]);
        if (PeggerAI::fiveOr21(played, validCards[0])) { points -= 1.5; }

        if (points > bestPoints)
        {
            bestPoints = points;
            bestIndx = v;
        }
        else if (points == bestPoints)
        {
            if (validCards[v].mValue > validCards[bestIndx].mValue)
            {
                bestPoints = points;
                bestIndx = v;
            }
        }
    }

    return validCards[bestIndx];
}
