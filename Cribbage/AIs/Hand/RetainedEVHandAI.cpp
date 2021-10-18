#include "RetainedEVHandAI.h"

#include <vector>

#include "../../Utils/Card.h"
#include "../../Utils/Hand.h"
#include "../../Utils/Deck.h"

#define CUT_PROB 1.0/46.0           // probability that a given card is cut

std::vector<Card> RetainedEVHandAI::select(const std::vector<Card>& dealt, bool isMyCrib)
{
    std::vector<Card> highestCards;
    float highestEV = -1;
    for (int i = 0; i < dealt.size() - 1; i++)          // run through all possible throws
    {
        for (int j = i + 1; j < dealt.size(); j++)
        {
            std::vector<Card> keep;                     // compute selection of cards to keep
            for (int k = 0; k < dealt.size(); k++)
            {
                if (k != i && k != j) { keep.push_back(dealt[k]); }
            }

            float ev = expectedValue(dealt, keep);
            if (ev > highestEV)
            {
                highestEV = ev;
                highestCards = keep;
            }
            else if (ev == highestEV)
            {
                if (Hand::sum(keep) < Hand::sum(highestCards))
                {
                    highestEV = ev;
                    highestCards = keep;
                }
            }
        }
    }
    return highestCards;
}

float RetainedEVHandAI::expectedValue(const std::vector<Card>& dealt, const std::vector<Card>& keep)
{
    std::vector<Card> options = Deck::newDeckOrder();   // compute the possible options
    for (int d = 0; d < dealt.size(); d++) { Card::erase(options, dealt[d]); }

    float ev = 0.0;                             // expected value for this hand
    for (int o = 0; o < options.size(); o++)
    {
        Card cut = options[o];
        Hand hand(keep, cut, false);        // init a possible hand
        ev += CUT_PROB * hand.score();      // update the expected value
    }
    return ev;
}
