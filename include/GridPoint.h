#ifndef GRIDPOINT_H
#define GRIDPOINT_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "Movable.h"
#include "Enums.h"

class Ship;

class GridSquare;

class Army;

class GridPoint
{
    public:

    GridPoint(int, int);
    virtual ~GridPoint() = default;
    Movable* getMovable() const;
    void setMovable(Movable*);
    GridPoint* getPointNeighbor(Direction) const;
    GridSquare* getSquareNeighbor(IntermediateDirection) const;
    void setPointNeighbor(Direction, GridPoint*);
    void setSquareNeighbor(IntermediateDirection, GridSquare*);
    bool enter(Army*);
    bool enter(Ship*);
    void exit(Movable*);
    void finishInitialization();
    sf::Vector2i getCoordinates() const;
    bool isLand() const;

    protected:

    private:
        const sf::Vector2i coordinates;
        Movable* movable;
        std::map<Direction, GridPoint* const> pointNeighbors;
        std::map<IntermediateDirection, GridSquare* const> squareNeighbors;
        bool isLandBool;
        bool isSeaBool;
};

#endif // GRIDPOINT_H
