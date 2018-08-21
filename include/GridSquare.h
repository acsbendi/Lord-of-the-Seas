//
// Created by Bendi on 1/21/2018.
//

#ifndef LORD_OF_THE_SEAS_GRIDSQUARE_H
#define LORD_OF_THE_SEAS_GRIDSQUARE_H

#include <memory>
#include <vector>
#include <unordered_set>
#include <map>
#include <SFML/Graphics.hpp>
#include "Enums.h"

using std::map;
using std::unordered_set;
using std::vector;
using std::unique_ptr;
using sf::Drawable;
using sf::Vector2i;
using sf::RenderTarget;

class Player;

class GridSquare : public Drawable
{
private:
    map<Direction, GridSquare* const> neighbors;
    map<Direction,Player*> edgeOwners;

    bool IsEdgeOwnedBy(Direction, const Player*, unordered_set<const GridSquare*>&) const;

public:
    void SetEdgeOwner(Direction, Player*);
    void SetNeighbor(Direction, GridSquare*);
    virtual bool IsLand() const = 0;
    virtual bool IsSea() const = 0;
    static vector<vector<unique_ptr<GridSquare>>> CreateGridSquares(int, int);

    virtual int GetValue() const = 0;

    /**
     * @brief Finds the owner of this GridSquare, if there is one.
     * @return The owner, if exists, nullptr otherwise.
     */
    Player* GetOwner(unordered_set<const GridSquare*>&) const;

    /**
     * @brief Finds a player who owns an edge in this GridSquare, if no such player exists,
     * and has a neighbor in the specified direction, recursively calls the same mehtod on it,
     * if it doesn't have it, return nullptr.
     * @return The possible owner, if exists, nullptr otherwise.
     */
    Player* GetPossibleOwner(Direction direction) const;

    /**
     * @brief Checks whether this GridSquare stops the game from ending.
     * @return True, if this GridSquare doesn't stop the game from ending, false if it does.
     */
    virtual bool CanEnd() const = 0;

    /**
     * @brief Checks whether this GridSquare is owned by the specified Player,
     * that is, whether it is in a territory of that player.
     * @return True, if this GridSquare is owned by the Player, false, if not.
     */
    bool IsOwnedBy(const Player* player, unordered_set<const GridSquare*>& previous) const;

protected:
    void DrawGridSquare(RenderTarget& target) const;
    GridSquare(int,int);

    const Vector2i coordinates;
};


#endif //LORD_OF_THE_SEAS_GRIDSQUARE_H
