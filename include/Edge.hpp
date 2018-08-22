//
// Created by Bendi on 8/23/2018.
//

#ifndef LORD_OF_THE_SEAS_LINE_HPP
#define LORD_OF_THE_SEAS_LINE_HPP

#include <SFML/System.hpp>
#include "Enums.h"

using sf::Vector2i;

struct Edge{
    Vector2i startCoordinates;
    Vector2i endCoordinates;
    Direction directionInSquare = up;
};

#endif //LORD_OF_THE_SEAS_LINE_HPP
