#ifndef __HAND_H__
#define __HAND_H__

#include <array>
#include <vector>

#include "Card.h"

class Hand
{

    std::array<Card, 4> mCards;
    Card mCut;
    bool mIsCrib;

public:

    Hand(const std::vector<Card>& cards, Card cut, bool crib = false);
    ~Hand();

    int score() const;

    int pairScore() const;
    int fifteenScore() const;
    int runScore() const;
    int flushScore() const;
    int nobsScore() const;

    friend std::ostream& operator<<(std::ostream& os, const Hand& hand);

    static int sum(const std::vector<Card>& cards);
    static bool isRun(std::vector<Card> cards);

};

#endif
