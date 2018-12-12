//
// Created by acsbendi on 2018.10.04..
//

#ifndef LORD_OF_THE_SEAS_EDGEOWNERCHANGEDEVENT_HPP
#define LORD_OF_THE_SEAS_EDGEOWNERCHANGEDEVENT_HPP


#include "PlayerProxy.h"
#include "../utils/Enums.h"

struct EdgeOwnerChangedEvent {
    PlayerProxy previousOwner;
    PlayerProxy newOwner;
    Direction edgeDirection;
};


#endif //LORD_OF_THE_SEAS_EDGEOWNERCHANGEDEVENT_HPP
