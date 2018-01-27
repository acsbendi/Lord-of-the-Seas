#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Player.h"
#include "IWindowEventObserver.h"


class Game : public IPlayerObserver, public IWindowEventObserver {
public:
    /**
     * @brief Constructs a new Game object, also creating players and the map.
     */
    Game();

    /**
     * @brief If one player has finished their turn, the other player needs to be notified.
     */
    void onTurnEnd() override;

    /**
     * @brief After every successful move, checks whether the game has ended or not.
     */
    void onMove() override;

    /**
     * @brief After the window of the map has been closed,
     * the Game stops asking for user input and the application exits as well.
     */
    void onExit() override;

    /**
     * @brief This method has to be called to start the game.
     * Asks for user input until the game is over, or the user exits the application.
     */
    void playGame();

protected:

    private:

        Map map; ///< Map object belonging to this Game.
        std::unique_ptr<Player> player1; ///< The first player playing this game.
        std::unique_ptr<Player> player2; ///< The second player playing this game.
        Player* currentPlayer; ///< The player who currently gets to move its pieces.
        bool gameEnd; ///< Has the game ended?
        bool turnEnd; ///< Has the turn of the currentPlayer ended?

    /**
     * @brief Checks if the game has already ended, if so, calls the exit handler function.
     */
        void checkEnd();
};

#endif // GAME_H
