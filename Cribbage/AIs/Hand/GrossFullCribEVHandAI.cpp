#include "GrossFullCribEVHandAI.h"

#include <vector>
#include <thread>

#include "../../Utils/Card.h"
#include "../../Utils/Hand.h"
#include "../../Utils/Deck.h"

std::vector<Card> GrossFullCribEVHandAI::select(const std::vector<Card>& dealt, bool isMyCrib)
{
    std::vector<std::thread> threads;
    int index = 0;
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

            threads.push_back(std::thread(&GrossFullCribEVHandAI::setGrossExpectedValue, this, index++, toKeep, toThrow, isMyCrib));
        }
    }

    for (int t = 0; t < SIX_CHOOSE_TWO; t++) { threads[t].join(); }             // finish the computation on each thread
    int highest = 0;
    for (int i = 1; i < SIX_CHOOSE_TWO; i++)                                    // find index with the largest gross expected value
    {
        if (mGrossEVs[i] > mGrossEVs[highest]) { highest = i; }
        else if (mGrossEVs[i] == mGrossEVs[highest])
        {
            if (Hand::sum(mToKeep[i]) < Hand::sum(mToKeep[highest]))
            {
                highest = i;
            }
        }
    }

    return mToKeep[highest];
}

void GrossFullCribEVHandAI::setGrossExpectedValue(int index, const std::vector<Card>& toKeep, const std::vector<Card>& toThrow, bool isMyCrib)
{
    float ev = grossExpectedValue(toKeep, toThrow, isMyCrib);
    mGrossEVs[index] = ev;
    mToKeep[index] = toKeep;
}


float GrossFullCribEVHandAI::grossExpectedValue(const std::vector<Card>& toKeep, const std::vector<Card>& toThrow, bool isMyCrib)
{
    std::vector<Card> options = Deck::newDeckOrder();   // compute the possible options
    for (int k = 0; k < toKeep.size(); k++)  { Card::erase(options, toKeep[k]); }
    for (int t = 0; t < toThrow.size(); t++) { Card::erase(options, toThrow[t]); }

    float ev = 0.0;                             // expected value for this hand
    for (int o = 0; o < options.size(); o++)
    {
        Card cut = options[o];
        Hand hand(toKeep, cut, false);      // init a possible hand
        ev += CUT_PROB * hand.score();      // update the expected value

        if (isMyCrib)                       // if it's our crib, add the expected value of the crib
        {
            ev += CUT_PROB * cribExpectedValue(toKeep, toThrow, cut);
        }
    }
    return ev;
}

float GrossFullCribEVHandAI::cribExpectedValue(const std::vector<Card>& toKeep, const std::vector<Card>& toThrow, const Card& cut)
{
    std::vector<Card> options = Deck::newDeckOrder();
    for (int k = 0; k < toKeep.size(); k++)  { Card::erase(options, toKeep[k]); }
    for (int t = 0; t < toThrow.size(); t++) { Card::erase(options, toThrow[t]); }
    Card::erase(options, cut);

    float ev = 0.0;
    for (int i = 0; i < options.size() - 1; i++)       // loop through all throw options from our opponent
    {
        for (int j = i + 1; j < options.size(); j++)
        {
            std::vector<Card> cribCards;
            cribCards.push_back(toThrow[0]);
            cribCards.push_back(toThrow[1]);
            cribCards.push_back(options[i]);
            cribCards.push_back(options[j]);

            Hand crib(cribCards, cut, true);
            ev += THROW_PROB * crib.score();
        }
    }
    return ev;
}
