#ifndef GRIDPOINT_H
#define GRIDPOINT_H

#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Enums.h"

using sf::Vector2i;
using std::map;

class Ship;
class GridSquare;
class Army;
class Movable;

class GridPoint {
public:
    GridPoint(int, int);
    virtual ~GridPoint() = default;
    Movable* GetMovable() const;
    void SetMovable(Movable*);
    GridPoint* GetPointNeighbor(Direction) const;
    GridSquare* GetSquareNeighbor(IntermediateDirection) const;
    void SetPointNeighbor(Direction, GridPoint*);
    void SetSquareNeighbor(IntermediateDirection, GridSquare*);
    bool Enter(Army*);
    bool Enter(Ship*);
    void Exit(Movable*);
    void FinishInitialization();
    Vector2i GetCoordinates() const;
    bool IsLand() const;

private:
    const Vector2i coordinates;
    Movable* movable;
    map<Direction, GridPoint* const> pointNeighbors;
    map<IntermediateDirection, GridSquare* const> squareNeighbors;
    bool isLandBool;
    bool isSeaBool;
};

#endif // GRIDPOINT_H
