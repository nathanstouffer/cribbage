#include "Hand.h"

#include <iostream>
#include <map>

#include "Card.h"
#include "Deck.h"

Hand::Hand(const std::vector<Card>& cards, Card cut, bool isCrib) :
      mCut(cut)
    , mIsCrib(isCrib)
{
    if (cards.size() != 4) { std::cerr << "cards is of size " << cards.size() << ", not 4" << std::endl; }
    for (int c = 0; c < 4; c++) { mCards[c] = cards[c]; }
}

Hand::~Hand() {}

int Hand::score() const
{
    int score = 0;
    score += pairScore();
    score += fifteenScore();
    score += runScore();
    score += flushScore();
    score += nobsScore();
    return score;
}

int Hand::pairScore() const
{
    int numPairs = 0;
    for (int i = 0; i < 4; i++)             // iterate over all 5 choose 2 pairs of cards
    {
        for (int j = i + 1; j < 5; j++)
        {
            Card card1 = mCards[i];
            Card card2;
            if (i == 4) { card2 = mCut; }
            else { card2 = mCards[j]; }

            if (card1.mName == card2.mName) { numPairs++; }
        }
    }

    return 2 * numPairs;
}

int Hand::fifteenScore() const
{
    std::vector<Card> subset;
    for (int c = 0; c < 4; c++)             // test set of five cards add to fifteen
    {
        subset.push_back(mCards[c]);
    }
    subset.push_back(mCut);
    if (Hand::sum(subset) == 15) { return 2; }

    int numFifteens = 0;

    for (int i = 0; i < 5; i++)             // check if sets of four cards add to fifteen
    {
        subset.clear();
        for (int c = 0; c < 4; c++)
        {
            if (c != i) { subset.push_back(mCards[c]); }
        }
        if (i != 4) { subset.push_back(mCut); }
        if (Hand::sum(subset) == 15) { numFifteens++; }
    }

    for (int i = 0; i < 4; i++)             // check if sets of three cards add to fifteen
    {
        for (int j = i + 1; j < 5; j++)
        {
            subset.clear();
            for (int c = 0; c < 4; c++)
            {
                if (c != i && c != j) { subset.push_back(mCards[c]); }
            }
            if (j != 4) { subset.push_back(mCut); }
            if (Hand::sum(subset) == 15) { numFifteens++; }
        }
    }

    for (int i = 0; i < 4; i++)             // check if sets of two cards add to fifteen
    {
        for (int j = i + 1; j < 5; j++)
        {
            subset.clear();
            for (int c = 0; c < 4; c++)
            {
                if (c == i || c == j) { subset.push_back(mCards[c]); }
            }
            if (j == 4) { subset.push_back(mCut); }
            if (Hand::sum(subset) == 15) { numFifteens++; }
        }
    }

    return 2 * numFifteens;
}

int Hand::runScore() const
{
    std::vector<Card> subset;
    for (int c = 0; c < 4; c++)         // check if all five form a run
    {
        subset.push_back(mCards[c]);
    }
    subset.push_back(mCut);
    if (Hand::isRun(subset)) { return 5; }

    int numRuns = 0;

    for (int i = 0; i < 5; i++)             // check if sets of four cards are runs
    {
        subset.clear();
        for (int c = 0; c < 4; c++)
        {
            if (c != i) { subset.push_back(mCards[c]); }
        }
        if (i != 4) { subset.push_back(mCut); }
        if (Hand::isRun(subset)) { numRuns++; }
    }
    if (numRuns != 0) { return 4 * numRuns; }

    for (int i = 0; i < 4; i++)             // check if sets of three cards are runs
    {
        for (int j = i + 1; j < 5; j++)
        {
            subset.clear();
            for (int c = 0; c < 4; c++)
            {
                if (c != i && c != j) { subset.push_back(mCards[c]); }
            }
            if (j != 4) { subset.push_back(mCut); }
            if (Hand::isRun(subset)) { numRuns++; }
        }
    }
    if (numRuns != 0) { return 3 * numRuns; }

    return 0;
}

int Hand::flushScore() const
{
    std::map<Suit, int> counts;
    for (int c = 0; c < 4; c++)
    {
        counts[mCards[c].mSuit]++;
    }
    for (auto const& pair : counts)
    {
        Suit suit = pair.first;
        int count = pair.second;
        if (count == 4)
        {
            if (suit == mCut.mSuit) { return 5; }   // if the cut matches, no questions asked

            if (mIsCrib) { return 0; }              // cut doesn't match, so no flush in the crib
            else         { return 4; }
        }
    }
    return 0;
}

int Hand::nobsScore() const
{
    for (int c = 0; c < 4; c++)
    {
        if (mCards[c].mName == "jack")
        {
            if (mCards[c].mSuit == mCut.mSuit) { return 1; }
        }
    }

    return 0;
}

int Hand::sum(const std::vector<Card>& cards)
{
    int running = 0;
    for (int c = 0; c < cards.size(); c++)
    {
        running += cards[c].mValue;
    }
    return running;
}

bool Hand::isRun(std::vector<Card> cards)
{
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (int i = 1; i < cards.size(); i++)      // bubble sort for fun since input is so small
        {
            if (cards[i] < cards[i-1])
            {
                Card tmp = cards[i];
                cards[i] = cards[i-1];
                cards[i-1] = tmp;
                changed = true;
            }
        }
    }

    int nameIndex = Card::getNameIndex(cards[0].mName);
    for (int c = 1; c < cards.size(); c++)                  // iterate over sorted cards
    {
        if (Deck::sNames[++nameIndex] != cards[c].mName)    // check if next name is different than it should be
        {
            return false;
        }
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, const Hand& hand)
{
    os << "----- Cards -----    ------- Cut ------    ---- Is crib ----    ----- Score -----" << std::endl;
    os << hand.mCards[0];
    os << "      " << hand.mCut;
    os << "       " << (hand.mIsCrib ? "true " : "false");
    os << "                " << hand.score() << std::endl;

    for (int c = 1; c < hand.mCards.size(); c++)
    {
        os << hand.mCards[c] << std::endl;
    }
    return os;
}
