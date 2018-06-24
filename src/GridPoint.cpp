#include "GridPoint.h"
#include "GridSquare.h"
#include <iostream>

GridPoint::GridPoint(int x, int y) : movable{nullptr}, coordinates{x,y}
{

}

Movable* GridPoint::getMovable() const
{
    return movable;
}

void GridPoint::setMovable(Movable* m)
{
    movable = m;
}

GridPoint* GridPoint::getPointNeighbor(Direction direction) const{
    return pointNeighbors.at(direction);
}

GridSquare* GridPoint::getSquareNeighbor(IntermediateDirection intermediateDirection) const {
    return squareNeighbors.at(intermediateDirection);
}

bool GridPoint::enter(Army* coming) {
    if(movable) return false; //this point is occupied

    if(!isLandBool)
        return false; //armies can only move on land

    movable = coming;
    return true;
}

bool GridPoint::enter(Ship* coming) {
    if(movable) return false; //this point is occupied

    if(!isSeaBool)
        return false; //ships can only move on sea

    movable = coming;
    return true;
}

void GridPoint::exit(Movable* leaving) {
    if(leaving == movable)
        movable= nullptr;
}

void GridPoint::setPointNeighbor(Direction direction, GridPoint* gridPoint) {
    pointNeighbors.insert(std::pair<Direction,GridPoint* const>(direction,gridPoint));
}

void GridPoint::setSquareNeighbor(IntermediateDirection intermediateDirection, GridSquare *gridSquare) {
    squareNeighbors.insert(std::pair<IntermediateDirection,GridSquare* const>(intermediateDirection,gridSquare));
}

void GridPoint::finishInitialization() {
    isLandBool =(squareNeighbors.at(northwest) && squareNeighbors.at(northwest)->IsLand()) ||
                (squareNeighbors.at(northeast) && squareNeighbors.at(northeast)->IsLand()) ||
                (squareNeighbors.at(southeast) && squareNeighbors.at(southeast)->IsLand()) ||
                (squareNeighbors.at(southwest) && squareNeighbors.at(southwest)->IsLand());
    isSeaBool = (squareNeighbors.at(northwest) && squareNeighbors.at(northwest)->IsSea()) ||
                (squareNeighbors.at(northeast) && squareNeighbors.at(northeast)->IsSea()) ||
                (squareNeighbors.at(southeast) && squareNeighbors.at(southeast)->IsSea()) ||
                (squareNeighbors.at(southwest) && squareNeighbors.at(southwest)->IsSea());
}

sf::Vector2i GridPoint::getCoordinates() const
{
    return coordinates;
}

bool GridPoint::isLand() const{
    return isLandBool;
}

