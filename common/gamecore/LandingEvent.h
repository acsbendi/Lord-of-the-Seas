//
// Created by acsbendi on 2018.09.29..
//

#ifndef LORD_OF_THE_SEAS_LANDINGEVENT_H
#define LORD_OF_THE_SEAS_LANDINGEVENT_H

#include "Ship.h"
#include "Player.h"
#include "Army.h"
#include "../utils/Enums.h"


struct LandingEvent{
    const Army& army;
    const Ship& ship;
    const Player& owner;
    Direction direction;
};

#endif //LORD_OF_THE_SEAS_LANDINGEVENT_H
