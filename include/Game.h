#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Player.h"


class Game
{
    public:
        Game();
        virtual ~Game() = default;
        void playGame();

    protected:

    private:
        static int NUMBER_OF_SHIP_MOVES;
        static int NUMBER_OF_ARMY_MOVES;

        Map map;
        std::unique_ptr<Player> player1;
        std::unique_ptr<Player> player2;
        bool end;

        void move(const std::unique_ptr<Player>&);
        void checkEnd();
        void landArmy(const std::unique_ptr<Player>&);
        Direction getSelectedDirection();
};

#endif // GAME_H
