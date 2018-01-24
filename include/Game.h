#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Player.h"
#include "IInputHandlerObserver.h"


class Game : public IPlayerObserver, public IInputHandlerObserver
{
    public:
        Game();
        void onTurnEnd() override;
        void onMove() override;
        void onExit() override;
        void onDirectionSelected(Direction) override;
        void onConfirmation(bool ) override;
        void playGame();

    protected:

    private:

        Map map;
        std::unique_ptr<Player> player1;
        std::unique_ptr<Player> player2;
        Player* currentPlayer;
        bool end;
        bool turnEnd;

        void checkEnd();
};

#endif // GAME_H
