#ifndef MAP_H
#define MAP_H

#include <vector>
#include <memory>
#include "GridPoint.h"
#include "GridSquare.h"
#include "Player.h"
#include "../utils/Enums.h"
#include "IUserEventObserver.h"
#include "IPlayerObserver.h"

using std::vector;
using std::unique_ptr;
using std::unordered_set;

class GridSquare;
class IMapObserver;

class Map : public IPlayerObserver {
public:
    /**
     * @brief Constructs a Map object, also creating the window. By default the Map is active.
     */
    Map();
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
    void OnLanding(LandingEvent event) override;

private:
    vector<vector<unique_ptr<GridPoint>>> gridPoints; ///< Two-dimension vector containing all the grid points in the map.
    vector<vector<unique_ptr<GridSquare>>> gridSquares; ///< Two-dimension vector containing all the grid squares in the map.
    vector<IMapObserver *> observers;
    int width;
    int height;

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
    void CheckForPoints(const GridSquare* gridSquareToCheck, unordered_set<const GridSquare*>& previouslyChecked) const;
    bool HasBeenChecked(const GridSquare* gridSquare, unordered_set<const GridSquare*>& previouslyChecked) const;

    friend class MapBuilder;
};

#endif // MAP_H
