#ifndef __CARD_H__
#define __CARD_H__

#include <string>
#include <vector>
#include <iostream>

enum Suit
{
    NoSuit, Spades, Diamonds, Clubs, Hearts
};

struct Card
{
    Suit mSuit;
    std::string mName;
    int mValue;

    Card();
    Card(Suit suit, std::string name, int val);

    Card& operator=(const Card& card);

    bool operator==(const Card& oth) const;
    bool operator!=(const Card& oth) const;
    bool operator<(const Card& oth) const;

    friend std::ostream& operator<<(std::ostream& os, const Card& c);

    static int getNameIndex(std::string name);
    static bool contains(const std::vector<Card>& vec, const Card& card);
    static void erase(std::vector<Card>& vec, const Card& card);
};

#endif
