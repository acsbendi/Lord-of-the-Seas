#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Player.h"


class Game
{
    public:
        Game();
        virtual ~Game();
        void playGame();

    protected:

    private:
        static int NUMBER_OF_MOVES;

        Map map;
        std::unique_ptr<Player> player1;
        std::unique_ptr<Player> player2;

        void move(const std::unique_ptr<Player>&);
        bool hasEnded() const;
        void landArmy(const std::unique_ptr<Player>&);
        Direction getSelectedDirection();
};

#endif // GAME_H
