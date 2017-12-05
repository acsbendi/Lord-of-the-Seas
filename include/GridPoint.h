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
        virtual ~GridSquare();
        std::shared_ptr<Player> getEdgeOwner(Direction) const;
        void setEdgeOwner(Direction,const std::shared_ptr<Player>&);
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
        std::vector<std::shared_ptr<Player>> edgeOwners;
        const sf::Vector2i coordinates;

};

        GridPoint(GridSquareType,int,int);
        ~GridPoint();
        std::shared_ptr<Movable> getMovable() const;
        void setMovable(std::shared_ptr<Movable>);
        bool isOwner(const Map&,const std::shared_ptr<Player>&) const;
        GridSquare& getGridSquare();
        const GridSquare& getGridSquare() const;

    protected:

    private:

        std::shared_ptr<Movable> movable;
        GridSquare gridSquare;

        bool isOwnerHelper(const GridPoint*,std::vector<const GridPoint*>&,const Map&,const std::shared_ptr<Player>&) const;
        bool isOwnerHelper2(const GridPoint*,std::vector<const GridPoint*>&,const Map&,const std::shared_ptr<Player>&, Direction) const;
};

#endif // GRIDPOINT_H
