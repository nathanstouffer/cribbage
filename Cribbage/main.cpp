#include "Game/Player.h"
#include "Game/Game.h"
#include "Utils/Random.h"
#include "AIs/Hand/HandAI.h"
#include "AIs/Pegger/PeggerAI.h"

#include <ctime>
#include <iostream>

void compareRandom()
{
    Player player1(HandAIEnum::RandomH, PeggerAIEnum::RandomP);
    Player player2(HandAIEnum::RandomH, PeggerAIEnum::RandomP);

    int oneWins = 0, twoWins = 0;
    int numGames = 5000;
    for (int i = 0; i < numGames; i++)
    {
        Game game(player1, player2);
        game.play();
        Winner winner = game.winner();

        if (winner == Winner::FirstPlayer)  { oneWins++; }
        if (winner == Winner::SecondPlayer) { twoWins++; }
        if (winner == Winner::None)
        {
            std::cout << "Bad state, nobody won." << std::endl;
        }
    }

    int oneWinPerc = 100*((float)oneWins / numGames);
    int twoWinPerc = 100*((float)twoWins / numGames);

    std::cout << "Player 1 win rate: " << oneWinPerc << "%" << std::endl;
    std::cout << "Player 2 win rate: " << twoWinPerc << "%" << std::endl;
}

void battle(const Player& player1, const Player& player2, int numGames)
{
    time_t start = std::time(NULL);
    int oneWins = 0, twoWins = 0;
    for (int i = 0; i < numGames; i++)
    {
        if (i % (numGames/10) == 0) {                                           // intermittent status update
            time_t current = std::time(NULL);                                   // get current time
            std::cout << (int)(100*i/(double)numGames) << "% complete  ";
            std::cout << current-start << " seconds passed" << std::endl;
        }

        Game* game;
        if (i % 2 == 0) { game = new Game(player1, player2); }
        if (i % 2 == 1) { game = new Game(player2, player1); }

        game->play();
        Winner winner = game->winner();

        if (i % 2 == 0)
        {
            if (winner == Winner::FirstPlayer)  { oneWins++; }
            if (winner == Winner::SecondPlayer) { twoWins++; }
        }
        if (i % 2 == 1)
        {
            if (winner == Winner::FirstPlayer)  { twoWins++; }
            if (winner == Winner::SecondPlayer) { oneWins++; }
        }

        if (winner == Winner::None)
        {
            std::cout << "Bad state, nobody won." << std::endl;
        }
        delete game;
    }

    int oneWinPerc = 100*((float)oneWins / numGames);
    int twoWinPerc = 100*((float)twoWins / numGames);

    std::cout << "Player 1 win rate: " << oneWinPerc << "%" << std::endl;
    std::cout << "Player 2 win rate: " << twoWinPerc << "%" << std::endl;
}

int main()
{

    Player randRand(HandAIEnum::RandomH,                        PeggerAIEnum::RandomP);
    Player retainedRand(HandAIEnum::RetainedEVH,                PeggerAIEnum::RandomP);
    Player grossHalfRand(HandAIEnum::GrossHalfCribEVH,          PeggerAIEnum::RandomP);
    Player relativeHalfRand(HandAIEnum::RelativeHalfCribEVH,    PeggerAIEnum::RandomP);
    Player grossFullRand(HandAIEnum::GrossFullCribEVH,          PeggerAIEnum::RandomP);
    Player relativeFullRand(HandAIEnum::RelativeFullCribEVH,    PeggerAIEnum::RandomP);

    Player randHeuristic(HandAIEnum::RandomH,                       PeggerAIEnum::HeuristicP);
    Player retainedHeuristic(HandAIEnum::RetainedEVH,               PeggerAIEnum::HeuristicP);
    Player grossHalfHeuristic(HandAIEnum::GrossHalfCribEVH,         PeggerAIEnum::HeuristicP);
    Player relativeHalfHeuristic(HandAIEnum::RelativeHalfCribEVH,   PeggerAIEnum::HeuristicP);
    Player grossFullHeuristic(HandAIEnum::GrossFullCribEVH,         PeggerAIEnum::HeuristicP);
    Player relativeFullHeuristic(HandAIEnum::RelativeFullCribEVH,   PeggerAIEnum::HeuristicP);

    battle(randRand, randHeuristic, 1000);

    Random::Instance()->destroy();

    return 0;
}
