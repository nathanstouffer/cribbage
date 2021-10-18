#include "Card.h"

#include <array>
#include <string>

#include "Deck.h"

Card::Card() :
      mSuit(Suit::NoSuit)
    , mName("None")
    , mValue(0)
{}

Card::Card(Suit suit, std::string name, int val) :
      mSuit(suit)
    , mName(name)
    , mValue(val)
{
    if (mValue < 1 || mValue > 10)
    {
        std::cerr << "Error -- value too large: " << mValue << std::endl;
    }
}

Card& Card::operator=(const Card& card)
{
    mSuit = card.mSuit;
    mName = card.mName;
    mValue = card.mValue;
    return *this;
}

bool Card::operator==(const Card& oth) const
{
    return (mSuit == oth.mSuit) && (mName == oth.mName);
}

bool Card::operator!=(const Card& oth) const
{
    return !(*this == oth);
}

bool Card::operator<(const Card& oth) const
{
    int i = Card::getNameIndex(mName);
    int j = Card::getNameIndex(oth.mName);

    if (i < j) { return true; }
    else { return false; }
}

std::ostream& operator<<(std::ostream &os, const Card& c)
{
    std::string suit;
    if (c.mSuit == Suit::NoSuit)   { suit = "None    "; }
    if (c.mSuit == Suit::Spades)   { suit = "spades  "; }
    if (c.mSuit == Suit::Diamonds) { suit = "diamonds"; }
    if (c.mSuit == Suit::Clubs)    { suit = "clubs   "; }
    if (c.mSuit == Suit::Hearts)   { suit = "hearts  "; }

    std::string nameSpaces;
    if (c.mName == "ace")  { nameSpaces += "  "; }
    if (c.mName == "two")  { nameSpaces += "  "; }
    if (c.mName == "four") { nameSpaces += " ";  }
    if (c.mName == "five") { nameSpaces += " ";  }
    if (c.mName == "six")  { nameSpaces += "  "; }
    if (c.mName == "nine") { nameSpaces += " ";  }
    if (c.mName == "ten")  { nameSpaces += "  "; }
    if (c.mName == "jack") { nameSpaces += " ";  }
    if (c.mName == "king") { nameSpaces += " ";  }

    os << suit << "  " << c.mName << nameSpaces; // << " val: " << c.mValue;
    return os;
}

int Card::getNameIndex(std::string name)
{
    for (int n = 0; n < Deck::sNames.size(); n++)
    {
        if (Deck::sNames[n] == name)
        {
            return n;
        }
    }
    return -1;
}

bool Card::contains(const std::vector<Card>& vec, const Card& card)
{
    for (int v = 0; v < vec.size(); v++)
    {
        if (vec[v] == card) { return true; }
    }
    return false;
}

void Card::erase(std::vector<Card>& vec, const Card& card)
{
    int i = -1;
    bool stop = false;
    for (int v = 0; v < vec.size() && !stop; v++)
    {
        if (vec[v] == card) { i = v; stop = true; }
    }
    vec.erase(vec.begin()+i);
}
