//
// Created by Bendi on 9/1/2018.
//

#ifndef LORD_OF_THE_SEAS_MAPCREATOR_HPP
#define LORD_OF_THE_SEAS_MAPCREATOR_HPP

#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

class GridSquare;

class MapCreator {
public:
    struct Position{
        int xCoordinate;
        int yCoordinate;

        bool operator==(const Position& other) const;
    };

    MapCreator(int width, int height,
               vector<Position> lands = {{19,20},{21,20},{20,21},{20,22},{20,19},{19,19},{19,18},{5,9},{6,8},{7,8},{6,9},{7,9},{5,7},{4,10},{4,9}},
               vector<Position> treasures = {{20,20},{5,8}});
    vector<vector<unique_ptr<GridSquare>>> GetGridSquares() const;

private:
    int width;
    int height;
    vector<Position> lands;
    vector<Position> treasures;

    vector<vector<unique_ptr<GridSquare>>> CreateGridSquareLists() const;
    void FillGridSquareLists(vector<vector<unique_ptr<GridSquare>>>& gridSquares) const;
};


#endif //LORD_OF_THE_SEAS_MAPCREATOR_HPP
