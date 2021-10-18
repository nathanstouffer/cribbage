#ifndef __DECK_H__
#define __DECK_H__

#include <vector>
#include <array>
#include <iostream>

#include "Card.h"

#define DECKSIZE 52
#define SUITSIZE 13
#define NUMSUITS 4

class Deck
{

    void swap(int i, int j);
    void makeUnavailable(int i);

public:

    std::vector<Card> mAvailable;
    std::vector<Card> mUnavailable;
    Card mCut;

    Deck();
    ~Deck();

    void reset();
    void shuffle();

    Card cut();
    std::array<std::vector<Card>, 2> deal();

    static std::vector<Card> newDeckOrder();
    static const std::array<std::string, SUITSIZE> sNames;
    static const std::array<int, SUITSIZE> sValues;

    friend std::ostream& operator<<(std::ostream& os, const Deck& deck);

};

#endif
