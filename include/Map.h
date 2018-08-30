#ifndef MAP_H
#define MAP_H

#include <vector>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GridPoint.h"
#include "GridSquare.h"
#include "Player.h"
#include "Enums.h"
#include "IUserEventObserver.h"
#include "IPlayerObserver.h"
#include "IWindowEventObserver.h"

using std::vector;
using std::unique_ptr;
using std::unordered_set;
using sf::RenderWindow;

class GridSquare;

class IMapObserver;

class Map : public IPlayerObserver {
public:
    static const int WIDTH = 40;   ///< The number of the columns in the grid structure of the map.
    static const int HEIGHT = 30;  ///< The number of the rows in the grid structure of the map.

    /**
     * @brief Constructs a Map object, also creating the window. By default the Map is active.
     */
    Map();
/**
 * @brief Initializes the map's structure with the specified players.
 * @param player1 The first player to play on this map.
 * @param player2 The second player to play on this map.
 */
    void InitializeGrid(Player *player1, Player *player2);
    /**
     * @brief Sets the scores of all players at the end of the game.
     */
    void CountScore() const;
    /**
     * @brief After every successful move, the map needs to updated on the window.
     */
    void OnMove() override;
    /**
     * @brief Checks if there is any unowned treasure square, in which case the game doesn't end.
     * @return True, if the game has ended, false if not.
     */
    bool CheckEnd();
    /**
     * @brief Method needed to implement the IPlayerObserver interface.
     */
    void OnTurnEnd() override;
    void Show(RenderWindow &);
    /**
 * @brief Attaches an observer to this map.
 * @param observer The observer to attach.
 */
    void Attach(IMapObserver *observer);
    /**
     * @brief Detaches an observer from this map.
     * @param observer The observer to detach.
     */
    void Detach(IMapObserver *observer);

private:
    vector<vector<unique_ptr<GridPoint>>> gridPoints; ///< Two-dimension vector containing all the grid points in the map.
    vector<vector<unique_ptr<GridSquare>>> gridSquares; ///< Two-dimension vector containing all the grid squares in the map.
    vector<IMapObserver *> observers;

/**
 * @brief Adds the points earned by owning the specified set of squares to the specified owner.
 * @param ownedSquares The owned squares.
 * @param owner The owner of the squares (player).
 */
    void AddPoints(unordered_set<const GridSquare *> ownedSquares, Player *owner) const;
/**
 * @brief Publishes an event to its subscribers, the state of the map may have been changed.
 */
    void Notify();
/**
 * @brief Sets the neighbor connections between squares and points, points and points, and squares and squares.
 */
    void SetNeighbors();
};

#endif // MAP_H
