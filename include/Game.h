#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Player.h"
#include "IWindowEventObserver.h"
#include "GameWindow.h"

using std::unique_ptr;

class GameWindow;

class Game : public IPlayerObserver, public IWindowEventObserver {
public:
    /**
     * @brief Constructs a new Game object, also creating players and the map.
     */
    Game();

    /**
     * @brief If one player has finished their turn, the other player needs to be notified.
     */
    void OnTurnEnd() override;

    /**
     * @brief After every successful move, checks whether the game has ended or not.
     */
    void OnMove() override;

    /**
     * @brief After the window of the map has been closed,
     * the Game stops asking for user input and the application exits as well.
     */
    void OnExit() override;

    /**
    * @brief This method has to be called to start the game.
    * Asks for user input until the game is over, or the user exits the application.
    * @param scoreOfPlayer1 The final score of the first player.
    * @param scoreOfPlayer2 The final score of the second player.
    */
    virtual void PlayGame(int &scoreOfPlayer1, int &scoreOfPlayer2);


protected:
    Game(unique_ptr<Player> player1, unique_ptr<Player> player2);

/**
 * @brief Checks if the game has already ended, if so, calls the exit handler function.
 */
    void CheckEnd();

    Map map; ///< Map object belonging to this game.
    GameWindow gameWindow; ///< The window that shows everything related to this game.
    unique_ptr<Player> player1; ///< The first player playing this game.
    unique_ptr<Player> player2; ///< The second player playing this game.
    Player* currentPlayer; ///< The player who currently gets to move its pieces.
    bool gameEnd; ///< Has the game ended?
    bool turnEnd; ///< Has the turn of the currentPlayer ended?


private:
};

#endif // GAME_H
