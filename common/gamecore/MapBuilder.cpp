//
// Created by Bendi on 9/1/2018.
//

#include <algorithm>
#include "MapBuilder.hpp"
#include "Land.h"
#include "Treasure.h"
#include "Water.h"
#include "Map.h"
#include "IMapBuilderObserver.hpp"


using std::move;
using std::find;
using std::make_unique;


MapBuilder::MapBuilder(int width, int height,
                               vector<Position> lands,
                               vector<Position> treasures) : width{width}, height{height},
                        lands{move(lands)}, treasures{move(treasures)} {
    topLeftPosition = {
            .xCoordinate = 0,
            .yCoordinate = 0
    };
    bottomRightPosition = {
            .xCoordinate = width - 2,
            .yCoordinate = height - 2
    };
}

void MapBuilder::BuildMap(Map& map, Ship& topLeftShip, Ship& bottomRightShip){
    InitializeGrid();
    InjectMapMembers(map);
    SetShipPositions(map, topLeftShip, bottomRightShip);
}

void MapBuilder::BuildMap(Map& map){
    InitializeGrid();

    InjectMapMembers(map);
}

void MapBuilder::InjectMapMembers(Map& map) {
    map.height = height;
    map.width = width;
    map.gridSquares = move(gridSquares);
    map.gridPoints = move(gridPoints);
}

void MapBuilder::SetShipPositions(Map& map, Ship& topLeftShip, Ship& bottomRightShip) const{
    SetShipPositions(topLeftShip, bottomRightShip,
                     *(map.gridPoints[topLeftPosition.yCoordinate][topLeftPosition.xCoordinate]),
                     *(map.gridPoints[bottomRightPosition.yCoordinate][bottomRightPosition.xCoordinate]));
}

void MapBuilder::SetShipPositions(Ship& topLeftShip, Ship& bottomRightShip,
        GridPoint& topLeftGridPoint, GridPoint& bottomRightGridPoint) const {
    topLeftGridPoint.SetMovable(&topLeftShip);
    topLeftShip.SetCurrentLocation(&topLeftGridPoint);
    bottomRightGridPoint.SetMovable(&bottomRightShip);
    bottomRightShip.SetCurrentLocation(&bottomRightGridPoint);
    NotifyOnShipPositionsSet(topLeftShip, bottomRightShip);
}

void MapBuilder::InitializeGrid()
{
    CreateGridSquares();
    CreateGridPoints();
    SetNeighbors();
    NotifyOnFinishInitialization();
}

void MapBuilder::CreateGridSquares(){
    CreateGridSquareLists();
    FillGridSquareListsAndCreateGridSquareViews();
}

void MapBuilder::CreateGridPoints() {
    CreateGridPointLists();
    FillGridPointLists();
}

void MapBuilder::NotifyOnFinishInitialization() {
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            gridPoints[i][j]->FinishInitialization();
}


void MapBuilder::CreateGridPointLists() {
    for(int i = 0; i < height; i++){
        gridPoints.emplace_back(static_cast<unsigned>(width));
    }
}

void MapBuilder::FillGridPointLists() {
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            gridPoints[i][j] = make_unique<GridPoint>();
}

void MapBuilder::CreateGridSquareLists() {
    for(int i = 0; i < height-1; i++){
        gridSquares.emplace_back(static_cast<unsigned>(width-1));
    }
}

void MapBuilder::FillGridSquareListsAndCreateGridSquareViews(){
    for(int i = 0; i < height-1; i++){
        for(int j = 0; j < width-1; j++) {
            if (find(lands.begin(), lands.end(), Position{j, i}) != lands.end()) {
                gridSquares[i][j] = make_unique<Land>();
            } else if (find(treasures.begin(), treasures.end(), Position{j, i}) != treasures.end()) {
                gridSquares[i][j] = make_unique<Treasure>();
            } else {
                gridSquares[i][j] = make_unique<Water>();
            }
            NotifyOnGridSquarePositionSet(*gridSquares[i][j],{
                .xCoordinate = j,
                .yCoordinate = i
            });
        }
    }
}

void MapBuilder::SetNeighbors() {
    for(int i = 0; i < height; ++i)
        for(int j = 0; j < width; ++j){
            SetConnectionsBetweenPoints({j,i});
            SetConnectionsBetweenPointsAndSquares({j,i});
            SetConnectionsBetweenSquares({j,i});
        }
}

void MapBuilder::SetConnectionsBetweenPoints(const Position& positionOfGridPoint) {
    GridPoint& gridPoint = *gridPoints[positionOfGridPoint.yCoordinate][positionOfGridPoint.xCoordinate];
    GridPoint* topNeighbor = positionOfGridPoint.yCoordinate - 1 >= 0 ? gridPoints[ positionOfGridPoint.yCoordinate - 1][positionOfGridPoint.xCoordinate].get() : nullptr;
    GridPoint* leftNeighbor = positionOfGridPoint.xCoordinate - 1 >= 0 ? gridPoints[positionOfGridPoint.yCoordinate][positionOfGridPoint.xCoordinate - 1].get() : nullptr;
    GridPoint* bottomNeighbor =  positionOfGridPoint.yCoordinate + 1 < height ? gridPoints[positionOfGridPoint.yCoordinate + 1][positionOfGridPoint.xCoordinate].get() : nullptr;
    GridPoint* rightNeighbor = positionOfGridPoint.xCoordinate + 1 < width ? gridPoints[positionOfGridPoint.yCoordinate][positionOfGridPoint.xCoordinate + 1].get() : nullptr;

    gridPoint.SetPointNeighbor(up, topNeighbor);
    gridPoint.SetPointNeighbor(left, leftNeighbor);
    gridPoint.SetPointNeighbor(down, bottomNeighbor);
    gridPoint.SetPointNeighbor(right, rightNeighbor);
}

void MapBuilder::SetConnectionsBetweenPointsAndSquares(const Position& positionOfGridPoint) {
    GridPoint& gridPoint = *gridPoints[positionOfGridPoint.yCoordinate][positionOfGridPoint.xCoordinate];
    GridSquare* topRightNeighbor = positionOfGridPoint.yCoordinate - 1 >= 0 && positionOfGridPoint.xCoordinate - 1 >= 0 ? gridSquares[positionOfGridPoint.yCoordinate - 1][positionOfGridPoint.xCoordinate - 1].get() : nullptr;
    GridSquare* topLeftNeighbor = positionOfGridPoint.yCoordinate - 1 >= 0 && positionOfGridPoint.xCoordinate + 1 < width ? gridSquares[positionOfGridPoint.yCoordinate - 1][positionOfGridPoint.xCoordinate].get() : nullptr;
    GridSquare* bottomLeftNeighbor =  positionOfGridPoint.yCoordinate + 1 < height && positionOfGridPoint.xCoordinate + 1 < width ? gridSquares[positionOfGridPoint.yCoordinate][positionOfGridPoint.xCoordinate].get() : nullptr;
    GridSquare* bottomRightNeighbor = positionOfGridPoint.yCoordinate + 1 < height && positionOfGridPoint.xCoordinate - 1 >= 0 ? gridSquares[positionOfGridPoint.yCoordinate][positionOfGridPoint.xCoordinate - 1].get() : nullptr;

    gridPoint.SetSquareNeighbor(northwest, topRightNeighbor);
    gridPoint.SetSquareNeighbor(northeast, topLeftNeighbor);
    gridPoint.SetSquareNeighbor(southeast, bottomLeftNeighbor);
    gridPoint.SetSquareNeighbor(southwest, bottomRightNeighbor);
}

void MapBuilder::SetConnectionsBetweenSquares(const Position& positionOfGridSquare) {
    if(ExistsGridSquare(positionOfGridSquare)){
        GridSquare& gridSquare = *gridSquares[positionOfGridSquare.yCoordinate][positionOfGridSquare.xCoordinate];
        GridSquare* topNeighbor =  positionOfGridSquare.yCoordinate - 1 >= 0 ? gridSquares[positionOfGridSquare.yCoordinate - 1][positionOfGridSquare.xCoordinate].get() : nullptr;
        GridSquare* leftNeighbor = positionOfGridSquare.xCoordinate - 1 >= 0 ? gridSquares[positionOfGridSquare.yCoordinate][positionOfGridSquare.xCoordinate - 1].get() : nullptr;
        GridSquare* bottomNeighbor =  positionOfGridSquare.yCoordinate + 2 < height ? gridSquares[positionOfGridSquare.yCoordinate + 1][positionOfGridSquare.xCoordinate].get() : nullptr;
        GridSquare* rightNeighbor = positionOfGridSquare.xCoordinate + 2 < width ? gridSquares[positionOfGridSquare.yCoordinate][positionOfGridSquare.xCoordinate + 1].get() : nullptr;

        gridSquare.SetNeighbor(up, topNeighbor);
        gridSquare.SetNeighbor(left, leftNeighbor);
        gridSquare.SetNeighbor(down, bottomNeighbor);
        gridSquare.SetNeighbor(right, rightNeighbor);
    }
}

bool MapBuilder::ExistsGridSquare(const Position& positionOfGridSquare) {
    return positionOfGridSquare.xCoordinate + 1 < width && positionOfGridSquare.yCoordinate + 1 < height;
}

void MapBuilder::Attach(IMapBuilderObserver* observer) {
    observers.push_back(observer);
}

void MapBuilder::Detach(IMapBuilderObserver* observer) {
    observers.erase(remove(observers.begin(),
                           observers.end(), observer),observers.end());
}

void MapBuilder::NotifyOnShipPositionsSet(Ship& topLeftShip, Ship& bottomRightShip) const {
    NotifyOnShipPositionSet(topLeftShip,topLeftPosition);
    NotifyOnShipPositionSet(bottomRightShip,bottomRightPosition);
}

void MapBuilder::NotifyOnGridSquarePositionSet(GridSquare& gridSquare, Position position) const {
    for(IMapBuilderObserver* observer : observers)
        observer->OnGridSquarePositionSet(gridSquare, position);
}

void MapBuilder::NotifyOnShipPositionSet(Ship& ship, Position position) const {
    for(IMapBuilderObserver* observer : observers)
        observer->OnShipPositionSet(ship, position);
}

int MapBuilder::GetWidth() const {
    return width;
}

int MapBuilder::GetHeight() const {
    return height;
}


