#ifndef GAME_H
#define GAME_H

#include "../../common/gamecore/Map.h"
#include "../../common/gamecore/Player.h"
#include "../ui/IWindowEventObserver.h"
#include "../ui/GameWindow.h"

using std::unique_ptr;

class GameWindow;
class MapBuilder;

class Game : public IPlayerObserver, public IWindowEventObserver {
public:

    explicit Game(MapBuilder&& mapInitializer);
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
    void OnLanding(LandingEvent event) override;

protected:
    unique_ptr<Player> player1; ///< The first player playing this game.
    unique_ptr<Player> player2; ///< The second player playing this game.
    Map map; ///< Map object belonging to this game.
    GameWindow gameWindow; ///< The window that shows everything related to this game.
    Player* currentPlayer; ///< The player who currently gets to move its pieces.
    bool gameEnd; ///< Has the game ended?
    bool turnEnd; ///< Has the turn of the currentPlayer ended?


/**
 * @brief Checks if the game has already ended, if so, calls the exit handler function.
 */
    void CheckEnd();
    void CreateAttachments();

    Game(unique_ptr<Player>&& player1, unique_ptr<Player>&& player2, MapBuilder&& map);
};

#endif // GAME_H
