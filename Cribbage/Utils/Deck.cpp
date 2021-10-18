#include "Deck.h"

#include <vector>
#include <array>

#include "Card.h"
#include "Random.h"

const std::array<std::string, SUITSIZE> Deck::sNames = { "ace", "two", "three", "four", "five", "six", "seven",
                                                         "eight", "nine", "ten", "jack", "queen", "king" };

const std::array<int, SUITSIZE> Deck::sValues = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };

Deck::Deck()
{
    mAvailable = Deck::newDeckOrder();
    mCut = Card();
}

Deck::~Deck()
{
    mAvailable.clear();
    mUnavailable.clear();
}

void Deck::reset()
{
    for (int u = 0; u < mUnavailable.size(); u++)
    {
        mAvailable.push_back(mUnavailable[u]);
    }
    mUnavailable.clear();
    mCut = Card();
}

void Deck::shuffle()
{
    reset();
    for (int u = 0; u < mAvailable.size(); u++) // iterate over undealt cards and swap each card to random position
    {
        swap(u, Random::Instance()->randInt() % mAvailable.size());
    }
}

void Deck::swap(int i, int j)
{
    Card tmp = mAvailable[i];
    mAvailable[i] = mAvailable[j];
    mAvailable[j] = tmp;
}

void Deck::makeUnavailable(int i)
{
    Card tmp = mAvailable[i];
    mAvailable.erase(mAvailable.begin()+i);
    mUnavailable.push_back(tmp);
}

Card Deck::cut()
{
    int i = rand() % mAvailable.size();
    mCut = mAvailable[i];
    makeUnavailable(i);
    return mCut;
}

std::array<std::vector<Card>, 2> Deck::deal()
{
    std::array<std::vector<Card>, 2> arr;
    for (int i = 0; i < 6; i++) // deal six cards
    {
        for (int j = 0; j < 2; j++) // one to each person
        {
            arr[j].push_back(mAvailable[0]);
            makeUnavailable(0);
        }
    }
    return arr;
}

std::vector<Card> Deck::newDeckOrder()
{
    std::vector<Card> vec;
    for (int i = 0; i < NUMSUITS; i++)
    {
        for (int j = 0; j < SUITSIZE; j++)
        {
            Suit suit;
            switch (i)
            {
                case 0: suit = Suit::Spades;   break;
                case 1: suit = Suit::Diamonds; break;
                case 2: suit = Suit::Clubs;    break;
                case 3: suit = Suit::Hearts;   break;
            }
            int indx = j;
            if (i == 2 || i == 3) { indx = SUITSIZE - j - 1; }  // reverse if in second half
            vec.push_back(Card(suit, Deck::sNames[indx], Deck::sValues[indx]));
        }
    }

    return vec;
}

std::ostream& operator<<(std::ostream& os, const Deck& deck)
{
    os << "---- Available Cards ----" << std::endl;
    for (int a = 0; a < deck.mAvailable.size(); a++)
    {
        os << deck.mAvailable[a] << std::endl;
    }
    os << std::endl;

    os << "--- Unavailable Cards ---" << std::endl;
    for (int u = 0; u < deck.mUnavailable.size(); u++)
    {
        std::cout << deck.mUnavailable[u] << std::endl;
    }
    os << std::endl;

    os << "---------- Cut ----------" << std::endl;
    os << deck.mCut << std::endl;

    return os;
}
