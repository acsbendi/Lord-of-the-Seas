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
    enum Type {water, land, treasure};

    static sf::Texture waterTexture;
    static sf::Texture landTexture;
    static sf::Texture treasureTexture;
    static sf::Texture createTexture(std::string);

    const Type type;
    std::map<Direction, GridSquare* const> neighbors;
    std::map<Direction,Player*> edgeOwners;
    const sf::Vector2i coordinates;

    static sf::Texture& getTexture(Type);
    bool isEdgeOwnedBy(Direction, const Player*, std::unordered_set<const GridSquare *>&) const;

public:
    GridSquare(Type,int,int);
    const Player* getEdgeOwner(Direction) const;
    void setEdgeOwner(Direction,Player*);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    GridSquare* getNeighbor(Direction) const;
    void setNeighbor(Direction, GridSquare*);
    bool isLand() const;
    bool isSea() const;
    static std::vector<std::vector<std::unique_ptr<GridSquare>>> createGridSquares(int,int);

    int getValue() const;

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
    bool canEnd() const;

    /**
     * @brief Checks whether this GridSquare is owned by the specified Player,
     * that is, whether it is in a territory of that player.
     * @return True, if this GridSquare is owned by the Player, false, if not.
     */
    bool isOwnedBy(const Player* player, std::unordered_set<const GridSquare *>& previous) const;

protected:

};


#endif //LORD_OF_THE_SEAS_GRIDSQUARE_H
