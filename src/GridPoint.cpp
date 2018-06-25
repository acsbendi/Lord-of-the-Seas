#include "GridPoint.h"
#include "GridSquare.h"
#include "Army.h"
#include "Ship.h"
#include <iostream>

GridPoint::GridPoint(int x, int y) : movable{nullptr}, coordinates{x,y}
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

bool GridPoint::Enter(Army* coming) {
    if(movable) return false; //this point is occupied

    if(!isLandBool)
        return false; //armies can only move on land

    movable = coming;
    return true;
}

bool GridPoint::Enter(Ship* coming) {
    if(movable) return false; //this point is occupied

    if(!isSeaBool)
        return false; //ships can only move on sea

    movable = coming;
    return true;
}

void GridPoint::Exit(Movable* leaving) {
    if(leaving == movable)
        movable= nullptr;
}

void GridPoint::SetPointNeighbor(Direction direction, GridPoint* gridPoint) {
    pointNeighbors.insert(std::pair<Direction,GridPoint* const>(direction,gridPoint));
}

void GridPoint::SetSquareNeighbor(IntermediateDirection intermediateDirection, GridSquare* gridSquare) {
    squareNeighbors.insert(std::pair<IntermediateDirection,GridSquare* const>(intermediateDirection,gridSquare));
}

void GridPoint::FinishInitialization() {
    isLandBool =(squareNeighbors.at(northwest) && squareNeighbors.at(northwest)->IsLand()) ||
                (squareNeighbors.at(northeast) && squareNeighbors.at(northeast)->IsLand()) ||
                (squareNeighbors.at(southeast) && squareNeighbors.at(southeast)->IsLand()) ||
                (squareNeighbors.at(southwest) && squareNeighbors.at(southwest)->IsLand());
    isSeaBool = (squareNeighbors.at(northwest) && squareNeighbors.at(northwest)->IsSea()) ||
                (squareNeighbors.at(northeast) && squareNeighbors.at(northeast)->IsSea()) ||
                (squareNeighbors.at(southeast) && squareNeighbors.at(southeast)->IsSea()) ||
                (squareNeighbors.at(southwest) && squareNeighbors.at(southwest)->IsSea());
}

sf::Vector2i GridPoint::GetCoordinates() const
{
    return coordinates;
}

bool GridPoint::IsLand() const{
    return isLandBool;
}

