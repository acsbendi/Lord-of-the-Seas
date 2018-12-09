//
// Created by acsbendi on 2018.10.06..
//

#ifndef LORD_OF_THE_SEAS_POSITION_HPP
#define LORD_OF_THE_SEAS_POSITION_HPP

#include "../utils/Enums.h"

struct Position {
    int xCoordinate;
    int yCoordinate;

    inline bool operator==(const Position& other) const {
        return this->xCoordinate == other.xCoordinate && this->yCoordinate == other.yCoordinate;
    }

    inline Position NeighborPosition(Direction direction) const{
        switch (direction){
            case up:
                return {xCoordinate, yCoordinate - 1};
            case down:
                return {xCoordinate, yCoordinate + 1};
            case right:
                return {xCoordinate + 1, yCoordinate};
            case left:
                return {xCoordinate - 1, yCoordinate};
        }
    }
};


#endif //LORD_OF_THE_SEAS_POSITION_HPP
