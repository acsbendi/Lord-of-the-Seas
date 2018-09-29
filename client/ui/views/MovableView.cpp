//
// Created by Bendi on 9/9/2018.
//

#include "../../common/utils/Enums.h"
#include "../client/GUI/MovableView.hpp"

void MovableView::ChangePositionOnMove(Direction directionOfMove){
    switch(directionOfMove){
        case up:
            currentPosition = {currentPosition.x, currentPosition.y - 1};
            break;
        case down:
            currentPosition = {currentPosition.x, currentPosition.y + 1};
            break;
        case left:
            currentPosition = {currentPosition.x - 1, currentPosition.y};
            break;
        case right:
            currentPosition = {currentPosition.x + 1, currentPosition.y};
            break;
    }
}