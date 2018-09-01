//
// Created by Bendi on 9/1/2018.
//

#include <algorithm>
#include "MapCreator.hpp"
#include "Land.h"
#include "Treasure.h"
#include "Water.h"

using std::move;
using std::find;
using std::make_unique;

bool MapCreator::Position::operator==(const Position& other) const {
    return this->xCoordinate == other.xCoordinate && this->yCoordinate == other.yCoordinate;
}

MapCreator::MapCreator(int width, int height,
                       vector<Position> lands,
                       vector<Position> treasures) :
    width{width}, height{height}, lands{move(lands)}, treasures{move(treasures)} {}

vector<vector<unique_ptr<GridSquare>>> MapCreator::GetGridSquares() const {
    vector<vector<unique_ptr<GridSquare>>> gridSquares = CreateGridSquareLists();
    FillGridSquareLists(gridSquares);

    return gridSquares;
}

vector<vector<unique_ptr<GridSquare>>> MapCreator::CreateGridSquareLists() const {
    vector<vector<unique_ptr<GridSquare>>> gridSquares;

    for(int i = 0; i < height-1; i++){
        gridSquares.emplace_back(static_cast<unsigned>(width-1));
    }
    return gridSquares;
}

void MapCreator::FillGridSquareLists(vector<vector<unique_ptr<GridSquare>>>& gridSquares) const {
    for(int i = 0; i < height-1; i++){
        for(int j = 0; j < width-1; j++)
            if (find(lands.begin(),lands.end(),Position{i,j}) != lands.end())
                gridSquares[i][j] = make_unique<Land>(j,i);
            else if(find(treasures.begin(),treasures.end(),Position{i,j}) != treasures.end())
                gridSquares[i][j] = make_unique<Treasure>(j,i);
            else
                gridSquares[i][j] = make_unique<Water>(j,i);
    }
}
