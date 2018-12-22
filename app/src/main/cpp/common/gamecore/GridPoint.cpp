#include "GridPoint.h"
#include "GridSquare.h"
#include "Army.h"
#include "Ship.h"

using std::pair;

GridPoint::GridPoint() : movable{nullptr}
{

}

Movable* GridPoint::GetMovable() const
{
    return movable;
}

void GridPoint::SetMovable(Movable* m)
{
    movable = m;
}

GridPoint* GridPoint::GetPointNeighbor(Direction direction) const{
    return pointNeighbors.at(direction);
}

GridSquare* GridPoint::GetSquareNeighbor(IntermediateDirection intermediateDirection) const {
    return squareNeighbors.at(intermediateDirection);
}

bool GridPoint::Enter(Army* coming, Direction moveDirection) {
    if(movable) return false; //this point is occupied

    bool isLandInMoveDirection = IsLandInMoveDirection(moveDirection); //ships can only move on sea

    if(isLandInMoveDirection)
        movable = coming;

    return isLandInMoveDirection;
}

bool GridPoint::Enter(Ship* coming, Direction moveDirection) {
    if(movable) return false; //this point is occupied

    bool isSeaInMoveDirection = IsSeaInMoveDirection(moveDirection); //ships can only move on sea

    if(isSeaInMoveDirection)
        movable = coming;

    return isSeaInMoveDirection;
}

bool GridPoint::Land(Army* landingArmy){
    if(movable || !isLandBool) return false;

    movable = landingArmy;
    return true;
}

void GridPoint::Exit(Movable* leaving) {
    if(leaving == movable)
        movable= nullptr;
}

void GridPoint::SetPointNeighbor(Direction direction, GridPoint* gridPoint) {
    pointNeighbors.insert(pair<Direction,GridPoint* const>(direction,gridPoint));
}

void GridPoint::SetSquareNeighbor(IntermediateDirection intermediateDirection, GridSquare* gridSquare) {
    squareNeighbors.insert(pair<IntermediateDirection,GridSquare* const>(intermediateDirection,gridSquare));
}

void GridPoint::FinishInitialization() {
    isLandBool =(squareNeighbors.at(northwest) && squareNeighbors.at(northwest)->IsLand()) ||
                (squareNeighbors.at(northeast) && squareNeighbors.at(northeast)->IsLand()) ||
                (squareNeighbors.at(southeast) && squareNeighbors.at(southeast)->IsLand()) ||
                (squareNeighbors.at(southwest) && squareNeighbors.at(southwest)->IsLand()); //TODO direction-dependent?
}

bool GridPoint::IsSeaInMoveDirection(Direction moveDirection){
    switch (moveDirection){
        case right:
            return  (squareNeighbors.at(northwest) && squareNeighbors.at(northwest)->IsSea()) ||
                    (squareNeighbors.at(southwest) && squareNeighbors.at(southwest)->IsSea());
        case left:
            return  (squareNeighbors.at(northeast) && squareNeighbors.at(northeast)->IsSea()) ||
                    (squareNeighbors.at(southeast) && squareNeighbors.at(southeast)->IsSea());
        case up:
            return  (squareNeighbors.at(southeast) && squareNeighbors.at(southeast)->IsSea()) ||
                    (squareNeighbors.at(southwest) && squareNeighbors.at(southwest)->IsSea());
        case down:
            return  (squareNeighbors.at(northeast) && squareNeighbors.at(northeast)->IsSea()) ||
                    (squareNeighbors.at(northwest) && squareNeighbors.at(northwest)->IsSea());
    }
}

bool GridPoint::IsLandInMoveDirection(Direction moveDirection){
    switch (moveDirection){
        case right:
            return  (squareNeighbors.at(northwest) && squareNeighbors.at(northwest)->IsLand()) ||
                    (squareNeighbors.at(southwest) && squareNeighbors.at(southwest)->IsLand());
        case left:
            return  (squareNeighbors.at(northeast) && squareNeighbors.at(northeast)->IsLand()) ||
                    (squareNeighbors.at(southeast) && squareNeighbors.at(southeast)->IsLand());
        case up:
            return  (squareNeighbors.at(southeast) && squareNeighbors.at(southeast)->IsLand()) ||
                    (squareNeighbors.at(southwest) && squareNeighbors.at(southwest)->IsLand());
        case down:
            return  (squareNeighbors.at(northeast) && squareNeighbors.at(northeast)->IsLand()) ||
                    (squareNeighbors.at(northwest) && squareNeighbors.at(northwest)->IsLand());
    }
}
bool GridPoint::IsLand() const{
    return isLandBool;
}

