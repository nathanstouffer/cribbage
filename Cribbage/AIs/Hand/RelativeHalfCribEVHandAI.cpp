#include "RelativeHalfCribEVHandAI.h"

#include <vector>

#include "../../Utils/Card.h"
#include "../../Utils/Hand.h"
#include "../../Utils/Deck.h"

std::vector<Card> RelativeHalfCribEVHandAI::select(const std::vector<Card>& dealt, bool isMyCrib)
{
    std::vector<Card> highestCards;
    float highestEV = -9999.0;
    for (int i = 0; i < dealt.size() - 1; i++)          // run through all possible throws
    {
        for (int j = i + 1; j < dealt.size(); j++)
        {
            std::vector<Card> toKeep;                     // compute selection of cards to keep
            std::vector<Card> toThrow;
            for (int k = 0; k < dealt.size(); k++)
            {
                if (k != i && k != j) { toKeep.push_back(dealt[k]); }
                else                  { toThrow.push_back(dealt[k]); }
            }

            float ev = relativeHalfCribExpectedValue(toKeep, toThrow, isMyCrib);
            if (ev > highestEV)
            {
                highestEV = ev;
                highestCards = toKeep;
            }
            else if (ev == highestEV)
            {
                if (Hand::sum(toKeep) < Hand::sum(highestCards))
                {
                    highestEV = ev;
                    highestCards = toKeep;
                }
            }
        }
    }
    return highestCards;
}

float RelativeHalfCribEVHandAI::relativeHalfCribExpectedValue(const std::vector<Card>& toKeep, const std::vector<Card>& toThrow, bool isMyCrib)
{
    std::vector<Card> options = Deck::newDeckOrder();   // compute the possible options
    for (int k = 0; k < toKeep.size(); k++)  { Card::erase(options, toKeep[k]); }
    for (int t = 0; t < toThrow.size(); t++) { Card::erase(options, toThrow[t]); }

    float ev = -9999.0;                             // expected value for this hand
    for (int o = 0; o < options.size(); o++)
    {
        Card cut = options[o];
        Hand hand(toKeep, cut, false);      // init a possible hand
        ev += CUT_PROB * hand.score();      // update the expected value

        if (isMyCrib)                       // if it's our crib, add the expected value of the crib
        {
            ev += CUT_PROB * halfCribScore(toThrow, cut);
        }
        else                                // otherwise, subtract from the expected value
        {
            ev -= CUT_PROB * halfCribScore(toThrow, cut);
        }
    }
    return ev;
}

int RelativeHalfCribEVHandAI::halfCribScore(const std::vector<Card>& toThrow, const Card& cut)
{
    int score = 0;
    std::vector<Card> cards = toThrow;
    cards.push_back(cut);

    for (int i = 0; i < 2; i++)                                         // check for pairs
    {
        for (int j = i + 1; j < 3; j++)
        {
            if (cards[i].mName == cards[j].mName) { score += 2; }
        }
    }

    if (Hand::sum(cards) == 15) { score += 2; }                         // check for fifteens
    else
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = i + 1; j < 3; j++)
            {
                if (cards[i].mValue + cards[j].mValue == 15) { score += 2; }
            }
        }
    }

    if (Hand::isRun(cards)) { score += 3; }                             // check for a run

    if (toThrow[0].mName == "jack" && toThrow[0].mSuit == cut.mSuit) { score += 1; }    // check for nobs
    if (toThrow[1].mName == "jack" && toThrow[1].mSuit == cut.mSuit) { score += 1; }

    return score;
}
