//
// Created by Bendi on 9/1/2018.
//

#ifndef LORD_OF_THE_SEAS_MAPCREATOR_HPP
#define LORD_OF_THE_SEAS_MAPCREATOR_HPP

#include <vector>
#include <memory>
#include "Position.hpp"

using std::vector;
using std::unique_ptr;

class GridSquare;
class Map;
class Player;
class GridPoint;
class Ship;
class IMapBuilderObserver;

class MapBuilder {
public:
    explicit MapBuilder(int width = 40, int height = 30,
                    vector<Position> lands = {{19,20},{21,20},{20,21},{20,22},{20,19},{19,19},{19,18},{5,9},{6,8},{7,8},{6,9},{7,9},{5,7},{4,10},{4,9}},
                    vector<Position> treasures = {{20,20},{5,8}});

    Map BuildMap(Ship& topLeftShip, Ship& bottomRightShip);
    Map BuildMap();
    void SetShipPositions(Map& map, Ship& topLeftShip, Ship& bottomRightShip) const;
    void Attach(IMapBuilderObserver* observer);
    void Detach(IMapBuilderObserver* observer);

private:
    Position bottomRightPosition;
    Position topLeftPosition;
    int width;
    int height;
    vector<vector<unique_ptr<GridPoint>>> gridPoints;
    vector<vector<unique_ptr<GridSquare>>> gridSquares;
    vector<Position> lands;
    vector<Position> treasures;
    vector<IMapBuilderObserver*> observers;

    void CreateGridSquares();
    void CreateGridSquareLists();
    void CreateGridPointLists();
    void FillGridSquareListsAndCreateGridSquareViews();
    void FillGridPointLists();
    void NotifyOnFinishInitialization();
    void CreateGridPoints();
    void SetNeighbors();
    void InitializeGrid();
    void SetShipPositions(Ship& topLeftShip, Ship& bottomRightShip);
    void SetConnectionsBetweenPoints(const Position& positionOfGridPoint);
    void SetConnectionsBetweenPointsAndSquares(const Position& positionOfGridPoint);
    void SetConnectionsBetweenSquares(const Position& positionOfGridSquare);
    bool ExistsGridSquare(const Position& positionOfGridSquare);
    void InjectMapMembers(Map&);
    void SetShipPositions(Ship& topLeftShip, Ship& bottomRightShip, GridPoint& topLeftGridPoint, GridPoint& bottomRightGridPoint) const;
    void NotifyOnShipPositionsSet(Ship& topLeftShip, Ship& bottomRightShip) const;
    void NotifyOnShipPositionSet(Ship&, Position) const;
    void NotifyOnGridSquarePositionSet(GridSquare&, Position) const;
};


#endif //LORD_OF_THE_SEAS_MAPCREATOR_HPP
