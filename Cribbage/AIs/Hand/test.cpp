#include "HandAI.h"

#include "../../Utils/Deck.h"
#include "../../Utils/Card.h"
#include "../../Utils/Hand.h"
#include "RandomHandAI.h"

int main()
{
    RandomHandAI rand;

    Deck deck;
    deck.shuffle();

    std::array<std::vector<Card>, 2> dealt = deck.deal();

    std::vector<Card> cards1 = rand.select(dealt[0], true);
    std::vector<Card> cards2 = rand.select(dealt[1], false);

    Card cut = deck.cut();

    Hand hand1(cards1, cut, false);
    Hand hand2(cards2, cut, false);

    std::cout << "Hand 1" << std::endl << hand1 << std::endl;
    std::cout << "Hand 2" << std::endl << hand2 << std::endl;

    return 0;
}
