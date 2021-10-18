#include "PeggerAI.h"

#include <vector>

#include "RandomPeggerAI.h"
#include "../../Utils/Card.h"
#include "../../Utils/Deck.h"
#include "../../Utils/Hand.h"

int main()
{
    RandomPeggerAI rand;

    Deck deck;
    deck.shuffle();

    std::array<std::vector<Card>, 2> dealt = deck.deal();

    std::vector<Card> cards1;
    for (int i = 0; i < 4; i++) { cards1.push_back(dealt[0][i]); }
    std::vector<Card> cards2;
    for (int i = 0; i < 4; i++) { cards2.push_back(dealt[1][i]); }

    std::vector<Card> played;
    played.push_back(dealt[0][4]);
    played.push_back(dealt[0][5]);

    Card card1 = rand.select(played, cards1);
    Card card2 = rand.select(played, cards2);

    std::cout << "------- Played -------" << std::endl;
    for (int p = 0; p < played.size(); p++)
    {
        std::cout << played[p] << std::endl;
    }
    std::cout << "sum: " << Hand::sum(played) << std::endl << std::endl;

    std::cout << "------- Hand 1 -------      ------- Choice -------" << std::endl;
    std::cout << cards1[0] << "             " << card1 << std::endl;
    for (int c = 1; c < cards1.size(); c++)
    {
        std::cout << cards1[c] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "------- Hand 2 -------      ------- Choice -------" << std::endl;
    std::cout << cards2[0] << "             " << card2 << std::endl;
    for (int c = 1; c < cards2.size(); c++)
    {
        std::cout << cards2[c] << std::endl;
    }

    return 0;
}
