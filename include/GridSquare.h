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
    std::map<Direction, GridSquare* const> neighbors;
    const Type type;
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
    Player* getOwner(std::unordered_set<const GridSquare*>&) const;
    Player* getPossibleOwner(Direction) const;
    bool canEnd() const;
    bool isOwnedBy(const Player*, std::unordered_set<const GridSquare *>&) const;

protected:

};


#endif //LORD_OF_THE_SEAS_GRIDSQUARE_H
