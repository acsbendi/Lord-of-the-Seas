#ifndef MAP_H
#define MAP_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "GridPoint.h"
#include "GridSquare.h"
#include "Player.h"
#include "Enums.h"
#include "IUserEventObserver.h"
#include "IPlayerObserver.h"
#include "IWindowEventObserver.h"

class GridSquare;

class Map : public IPlayerObserver
{
    public:
        static int GRID_SIDE;   ///< The side length of one grid block.
        static int MARGIN;  ///< The margin around the grid structure of the map.

    /**
     * @brief Constructs a Map object, also creating the window. By default the Map is active.
     */
        Map();

/**
 * @brief Initializes the map's structure with the specified players.
 * @param player1 The first player to play on this map.
 * @param player2 The second player to play on this map.
 */
        void initializeGrid(Player* player1,Player* player2);

    /**
     * @brief Sets the scores of all players at the end of the game.
     */
        void countScore() const;

    /**
     * @brief After every successful move, the map needs to updated on the window.
     */
        void onMove() override;

    /**
     * @brief Attaches a user event observer from this map.
     * @param observer The user event observer to attach.
     */
        void attachUserEventObserver(IUserEventObserver* observer);

    /**
     * @brief Detaches a user event observer from this map.
     * @param observer The user event observer to detach.
     */
        void detachUserEventObserver(IUserEventObserver* observer);

    /**
     * @brief Attaches a window event observer from this map.
     * @param observer The window event observer to attach.
     */
        void attachWindowEventObserver(IWindowEventObserver* observer);

    /**
     * @brief Detaches a window event observer from this map.
     * @param observer The window event observer to detach.
     */
        void detachWindowEventObserver(IWindowEventObserver* observer);

    /**
     * @brief Checks if there is any unowned treasure square, in which case the game doesn't end.
     * @return True, if the game has ended, false if not.
     */
        bool checkEnd();

    /**
     * @brief Loop for all user input. Waits for the next meaningful event,
     * notifies the appropriate observers, then returns.
     */
        void getInput();

    /**
     * @brief Method needed to implement the IPlayerObserver interface.
     */
        void onTurnEnd() override;

    /**
     * @brief Sets whether the map should create its events or not.
     * @param active Should the window create events?
     */
        void setActive(bool active);

    protected:

    private:

    static int WIDTH;   ///< The number of the columns in the grid structure of the map.
    static int HEIGHT;  ///< The number of the rows in the grid structure of the map.

    std::vector<std::vector<std::unique_ptr<GridPoint>>> gridPoints; ///< Two-dimension vector containing all the grid points in the map.
    std::vector<std::vector<std::unique_ptr<GridSquare>>> gridSquares; ///< Two-dimension vector containing all the grid squares in the map.
    std::vector<IUserEventObserver*> userEventObservers; ///< Vector storing the attached user event observers.
    std::vector<IWindowEventObserver*> windowEventObservers; ///< Vector storing the attached window event observers.

    sf::RenderWindow window; ///< The window on which the map is displayed.

    bool active; ///< Should the window create events?

/**
 * @brief Adds the points earned by owning the specified set of squares to the spcified owner.
 * @param ownedSquares The owned squares.
 * @param owner The owner of the squares (player).
 */
    void addPoints(std::unordered_set<const GridSquare*> ownedSquares, Player* owner) const;
    /**
     * @brief Refreshes the map, so that recent changes can appear graphically.
     */
    void refresh();
    /**
     * @brief Notifies the subscribed observers after the window containing the map has been closed.
     */
    void notifyOnExit() const;
    /**
     * @brief Notifies the subscribed observers after the user has selected a direction.
     */
    void notifyOnDirectionSelected(Direction) const;
    /**
     * @brief Notifies the subscribed observers whether the user has confirmed the action at hand.
     */
    void notifyOnConfirmation(bool) const;

    /**
     * @brief Sets the neighbor connections between squares and points, points and points, and squares and squares.
     */
    void setNeighbors();
};

#endif // MAP_H
