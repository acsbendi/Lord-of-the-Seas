#ifndef GRIDPOINT_H
#define GRIDPOINT_H

#include <map>
#include <memory>
#include "Enums.h"

using std::map;

class Ship;
class GridSquare;
class Army;
class Movable;

class GridPoint {
public:
    GridPoint();
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
    bool IsLand() const;

private:
    Movable* movable;
    map<Direction, GridPoint* const> pointNeighbors;
    map<IntermediateDirection, GridSquare* const> squareNeighbors;
    bool isLandBool;
    bool isSeaBool;
};

#endif // GRIDPOINT_H
