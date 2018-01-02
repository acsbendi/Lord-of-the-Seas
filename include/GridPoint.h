#ifndef GRIDPOINT_H
#define GRIDPOINT_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "Movable.h"
#include "Enums.h"

class Movable;

class Player;

class Map;

class GridPoint
{
    public:
        class GridSquare : public sf::Drawable
{
    public:
        GridSquare(GridSquareType,int,int);
        virtual ~GridSquare() = default;
        const Player* getEdgeOwner(Direction) const;
        void setEdgeOwner(Direction,const Player*);
        GridSquareType getType() const;
        sf::Vector2i getCoordinates() const;
        static sf::Texture& getTexture(GridSquareType);
        void draw(sf::RenderTarget&, sf::RenderStates) const override;

    protected:

    private:
        static sf::Texture waterTexture;
        static sf::Texture landTexture;
        static sf::Texture treasureTexture;
        static sf::Texture createTexture(std::string);

        const GridSquareType type;
        std::vector<const Player*> edgeOwners;
        const sf::Vector2i coordinates;

};

        GridPoint(GridSquareType,int,int);
        virtual ~GridPoint() = default;
        Movable* getMovable() const;
        void setMovable(Movable*);
        GridSquare& getGridSquare();
        const GridSquare& getGridSquare() const;

    protected:

    private:

        Movable* movable;
        GridSquare gridSquare;
};

#endif // GRIDPOINT_H
