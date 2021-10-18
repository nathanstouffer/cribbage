#include "Deck.h"
#include "Card.h"
#include "Hand.h"

int main()
{

    Deck deck;
    deck.shuffle();

    std::array<std::vector<Card>, 2> dealt = deck.deal();
    Card cut = deck.cut();

    std::vector<Card> cards1;
    for (int i = 0; i < 4; i++) { cards1.push_back(dealt[0][i]); }

    std::vector<Card> cards2;
    for (int i = 0; i < 4; i++) { cards2.push_back(dealt[1][i]); }

    Hand hand1(cards1, cut, false);
    Hand hand2(cards2, cut, false);

    std::cout << "Hand 1" << std::endl << hand1 << std::endl;
    std::cout << "Hand 2" << std::endl << hand2 << std::endl;

    return 0;
}
