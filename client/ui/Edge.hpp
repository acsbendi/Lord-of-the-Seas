//
// Created by Bendi on 8/23/2018.
//

#ifndef LORD_OF_THE_SEAS_LINE_HPP
#define LORD_OF_THE_SEAS_LINE_HPP

#include "../../common/utils/Enums.h"

struct Edge{
    Position startCoordinates{};
    Position endCoordinates{};
    Direction directionInSquare = up;
};

#endif //LORD_OF_THE_SEAS_LINE_HPP
