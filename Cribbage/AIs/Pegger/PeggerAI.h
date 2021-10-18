#ifndef __PEGGERAI_H__
#define __PEGGERAI_H__

#include <vector>

#include "../../Utils/Card.h"

enum PeggerAIEnum
{
    RandomP, HeuristicP
};

class PeggerAI
{
public:

    virtual ~PeggerAI() {}

    // returns the selected card to play
    // if no card can be played, returns Card()
    virtual Card select(const std::vector<Card>& played, const std::vector<Card>& avail) = 0;

    // returns the cards that actually can be played
    static std::vector<Card> valid(const std::vector<Card>& played, const std::vector<Card>& avail);

    // returns the number of points given by playing toPlay
    static int points(const std::vector<Card>& played, const Card& toPlay);

    // check if the sum is 5 or 21
    static bool fiveOr21(const std::vector<Card>& played, const Card& toPlay);

    static std::string enumToString(PeggerAIEnum peggerAIType);

    static PeggerAIEnum stringToEnum(std::string str);

};

#endif
