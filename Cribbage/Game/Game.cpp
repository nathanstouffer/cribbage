#include "Game.h"

#include <vector>
#include <array>
#include <algorithm>

#include "Player.h"
#include "../Utils/Card.h"
#include "../Utils/Deck.h"
#include "../Utils/Hand.h"

Game::Game(const Player& pOne, const Player& pTwo) :
      mP1(Player(pOne.mHandAIType, pOne.mPeggerAIType))
    , mP2(Player(pTwo.mHandAIType, pTwo.mPeggerAIType))
{}

void Game::play()
{
    mP1.mScore = 0;
    mP2.mScore = 0;
    Player* dealer    = &mP1;
    Player* notDealer = &mP2;
    while (winner() == Winner::None)
    {
        playRound(dealer, notDealer);
        Player* tmp = dealer;       // swap the dealer
        dealer = notDealer;
        notDealer = tmp;
    }
}

void Game::playRound(Player* dealer, Player* notDealer)
{
    mDeck.shuffle();
    std::array<std::vector<Card>, 2> dealt = mDeck.deal();
    std::vector<Card> notDealerCards = dealt[0];
    std::vector<Card> dealerCards    = dealt[1];

    std::vector<Card> notDealerKeep = notDealer->mHandAI->select(notDealerCards, false);
    std::vector<Card> dealerKeep    = dealer->mHandAI->select(dealerCards, true);

    std::vector<Card> cribCards = Game::constructCrib(notDealerCards, notDealerKeep,
                                                      dealerCards,    dealerKeep);

    Card cut = mDeck.cut();
    if (winner() == Winner::None)
    {
        if (cut.mName == "jack") { dealer->mScore += 2; }               // check for nibs
    }

    Hand notDealerHand(notDealerKeep, cut, false);
    Hand dealerHand(dealerKeep, cut, false);
    Hand crib(cribCards, cut, true);

    /*std::cout << "-------------------------------- Not Dealer Hand --------------------------------" << std::endl;
    std::cout << notDealerHand << std::endl;
    std::cout << "---------------------------------- Dealer Hand ----------------------------------" << std::endl;
    std::cout << dealerHand << std::endl;
    std::cout << "----------------------------------- Crib Hand -----------------------------------" << std::endl;
    std::cout << crib << std::endl;*/

    notDealer->mNotPegged.clear();
    notDealer->mPegged.clear();
    dealer->mNotPegged.clear();
    dealer->mPegged.clear();

    notDealer->mNotPegged = notDealerKeep;
    dealer->mNotPegged = dealerKeep;

    if (winner() == Winner::None) { playPegging(dealer, notDealer); }

    if (winner() == Winner::None)
    {
        notDealer->mScore += notDealerHand.score();
        if (winner() == Winner::None)
        {
            dealer->mScore += dealerHand.score();
            if (winner() == Winner::None)
            {
                dealer->mScore += crib.score();
            }
        }
    }

    //std::cout << mP1->mScore.getValue() << std::endl;
    //std::cout << mP2->mScore.getValue() << std::endl;
}

void Game::playPegging(Player* dealer, Player* notDealer)
{
    Player* first = notDealer;
    Player* second = dealer;
    bool run = (winner() == Winner::None);
    while (run)
    {
        Player* last = pegTo31(first, second);
        if (last == first)
        {
            first = second;
            second = last;
        }
        run = (first->mNotPegged.size() > 0) || (second->mNotPegged.size() > 0);
        run = run && (winner() == Winner::None);
    }
}

Player* Game::pegTo31(Player* first, Player* second)
{
    std::vector<Card> played;
    Player* last = first;
    bool run = (winner() == Winner::None);
    while (run)
    {
        int cantPlay = 0;                   // number of players who can't play
        if (winner() == Winner::None)
        {
            Card toPlay = first->mPeggerAI->select(played, first->mNotPegged);
            if (toPlay != Card())
            {
                first->mScore += PeggerAI::points(played, toPlay);
                first->markPegged(toPlay);
                played.push_back(toPlay);
                last = first;
            }
            else { cantPlay++; }
        }

        if (winner() == Winner::None)
        {
            Card toPlay = second->mPeggerAI->select(played, second->mNotPegged);
            if (toPlay != Card())
            {
                second->mScore += PeggerAI::points(played, toPlay);
                second->markPegged(toPlay);
                played.push_back(toPlay);
                last = second;
            }
            else { cantPlay++; }
        }

        run = (cantPlay < 2) && (winner() == Winner::None);
    }

    if (winner() == Winner::None)
    {
        if (Hand::sum(played) != 31) { last->mScore += 1; }        // add points for a go
    }
    return last;
}

Winner Game::winner()
{
    if (mP1.mScore > 120 && mP2.mScore > 120) {
        std::cout << "Both players have a score greater than 120" << std::endl;
        return Winner::None;
    }
    else if (mP1.mScore > 120)                { return Winner::FirstPlayer; }
    else if (mP2.mScore > 120)                { return Winner::SecondPlayer; }
    return Winner::None;
}

std::vector<Card> Game::constructCrib(const std::vector<Card>& dealt1,
                                      const std::vector<Card>& keep1,
                                      const std::vector<Card>& dealt2,
                                      const std::vector<Card>& keep2)
{
    std::vector<Card> cribCards;
    for (int d = 0; d < dealt1.size(); d++)
    {
        if (!Card::contains(keep1, dealt1[d]))
        {
            cribCards.push_back(dealt1[d]);
        }
    }
    for (int d = 0; d < dealt2.size(); d++)
    {
        if (!Card::contains(keep2, dealt2[d]))
        {
            cribCards.push_back(dealt2[d]);
        }
    }
    return cribCards;
}
