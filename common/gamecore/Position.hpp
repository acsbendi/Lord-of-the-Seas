//
// Created by acsbendi on 2018.10.06..
//

#ifndef LORD_OF_THE_SEAS_POSITION_HPP
#define LORD_OF_THE_SEAS_POSITION_HPP


struct Position {
    int xCoordinate;
    int yCoordinate;

    inline bool operator==(const Position& other) const {
        return this->xCoordinate == other.xCoordinate && this->yCoordinate == other.yCoordinate;
    }
};


#endif //LORD_OF_THE_SEAS_POSITION_HPP
