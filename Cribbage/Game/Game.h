#ifndef __GAME_H__
#define __GAME_H__

#include "../AIs/Hand/HandAI.h"
#include "../AIs/Pegger/PeggerAI.h"
#include "../Utils/Deck.h"
#include "Player.h"

enum Winner
{
    None, FirstPlayer, SecondPlayer
};

class Game
{

    Deck mDeck;

    // play a round (shuffle, deal, choose, cut, peg, and count)
    void playRound(Player* dealer, Player* notDealer);
    // play the pegging portion of the round
    void playPegging(Player* dealer, Player* notDealer);
    // play a round of pegging 31 (returns pointer to last person to play)
    Player* pegTo31(Player* first, Player* second);

public:

    Player mP1;
    Player mP2;

    Game(const Player& pOne, const Player& pTwo);

    // play the game until someone wins
    void play();            // play the whole game
    Winner winner();        // return an enum with the winner

    int getScore1() { return mP1.mScore.getValue(); }
    int getScore2() { return mP2.mScore.getValue(); }

    static std::vector<Card> constructCrib(const std::vector<Card>& dealt1,
                                           const std::vector<Card>& keep1,
                                           const std::vector<Card>& dealt2,
                                           const std::vector<Card>& keep2);

};

#endif
