#include "PeggerAI.h"

#include <vector>

#include "../../Utils/Card.h"
#include "../../Utils/Hand.h"

int PeggerAI::points(const std::vector<Card>& played, const Card& toPlay)
{
    int size = played.size();
    int points = 0;

    if (Hand::sum(played) + toPlay.mValue == 15)        // check if we are at fifteen
    {
        points += 2;
    }

    if (Hand::sum(played) + toPlay.mValue == 31)        // check if we are 31
    {
        points += 2;
    }

    // check for pairs and such
    std::string name = toPlay.mName;
    if (size >= 3)
    {
        if (played[size-1].mName == name && played[size-2].mName == name && played[size-3].mName == name)
        {
             points += 12;
        }
    }
    else if (size >= 3)
    {
        if (played[size-1].mName == name && played[size-2].mName == name)
        {
             points += 6;
        }
    }
    else if (size >= 1)
    {
        if (played[size-1].mName == name)
        {
             points += 2;
        }
    }

    bool run = true;
    for (int i = 0; i < size && run; i++)
    {
        if (size - i <= 3)          // check if we are looking at the last four cards played
        {
            bool match = true;
            int p;
            for (p = i; p < size && match; p++)
            {

            }
        }
    }

    // check for runs
    run = true;
    for (int i = size; i >= 2 && run; i--)
    {
        std::vector<Card> subset;
        subset.push_back(toPlay);
        for (int p = size - i; p < size; p++)
        {
            subset.push_back(played[p]);
        }
        if (Hand::isRun(subset))
        {
            points += subset.size();
            run = false;
        }
    }

    return points;
}

std::vector<Card> PeggerAI::valid(const std::vector<Card>& played, const std::vector<Card>& avail)
{
    std::vector<Card> validCards;
    int sum = Hand::sum(played);
    for (int a = 0; a < avail.size(); a++)
    {
        if (sum + avail[a].mValue <= 31)
        {
            validCards.push_back(avail[a]);
        }
    }
    return validCards;
}

bool PeggerAI::fiveOr21(const std::vector<Card>& played, const Card& toPlay)
{
    int sum = Hand::sum(played) + toPlay.mValue;
    return (sum == 5 || sum == 21);
}

std::string PeggerAI::enumToString(PeggerAIEnum peggerAIType)
{
    switch (peggerAIType)
    {
        case PeggerAIEnum::RandomP:         return "RandomP";           break;
        case PeggerAIEnum::HeuristicP:      return "HeuristicP";        break;
        default:                            return "No Pegger";
    }
}

PeggerAIEnum PeggerAI::stringToEnum(std::string str)
{
    if (str == "RandomP")                   { return PeggerAIEnum::RandomP; }
    if (str == "HeuristicP")                { return PeggerAIEnum::HeuristicP; }
    std::cerr << "should not be here in PeggerAI::stringToEnum()" << std::endl;
    return PeggerAIEnum::RandomP;
}
