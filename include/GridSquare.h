//
// Created by Bendi on 1/21/2018.
//

#ifndef LORD_OF_THE_SEAS_GRIDSQUARE_H
#define LORD_OF_THE_SEAS_GRIDSQUARE_H

#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "Player.h"

class GridSquare : public sf::Drawable
{
private:
    std::map<Direction, GridSquare* const> neighbors;
    std::map<Direction,Player*> edgeOwners;

    bool isEdgeOwnedBy(Direction, const Player*, std::unordered_set<const GridSquare *>&) const;

public:
    const Player* getEdgeOwner(Direction) const;
    void setEdgeOwner(Direction,Player*);
    GridSquare* getNeighbor(Direction) const;
    void setNeighbor(Direction, GridSquare*);
    virtual bool isLand() const = 0;
    virtual bool isSea() const = 0;
    static std::vector<std::vector<std::unique_ptr<GridSquare>>> createGridSquares(int,int);

    virtual int getValue() const = 0;

    /**
     * @brief Finds the owner of this GridSquare, if there is one.
     * @return The owner, if exists, nullptr otherwise.
     */
    Player* getOwner(std::unordered_set<const GridSquare*>&) const;

    /**
     * @brief Finds a player who owns an edge in this GridSquare, if no such player exists,
     * and has a neighbor in the specified direction, recursively calls the same mehtod on it,
     * if it doesn't have it, return nullptr.
     * @return The possible owner, if exists, nullptr otherwise.
     */
    Player* getPossibleOwner(Direction direction) const;

    /**
     * @brief Checks whether this GridSquare stops the game from ending.
     * @return True, if this GridSquare doesn't stop the game from ending, false if it does.
     */
    virtual bool canEnd() const = 0;

    /**
     * @brief Checks whether this GridSquare is owned by the specified Player,
     * that is, whether it is in a territory of that player.
     * @return True, if this GridSquare is owned by the Player, false, if not.
     */
    bool isOwnedBy(const Player* player, std::unordered_set<const GridSquare *>& previous) const;

protected:
    static sf::Texture createTexture(std::string);
    void drawGridSquare(sf::RenderTarget& target) const;
    GridSquare(int,int);

    const sf::Vector2i coordinates;
};


#endif //LORD_OF_THE_SEAS_GRIDSQUARE_H
