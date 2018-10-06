//
// Created by Bendi on 9/9/2018.
//

#include "../../../common/utils/Enums.h"
#include "MovableView.hpp"
#include "../GameWindow.h"

void MovableView::ChangePositionOnMove(Direction directionOfMove){
    switch(directionOfMove){
        case up:
            currentPosition = {currentPosition.xCoordinate, currentPosition.yCoordinate - 1};
            break;
        case down:
            currentPosition = {currentPosition.xCoordinate, currentPosition.yCoordinate + 1};
            break;
        case left:
            currentPosition = {currentPosition.xCoordinate - 1, currentPosition.yCoordinate};
            break;
        case right:
            currentPosition = {currentPosition.xCoordinate + 1, currentPosition.yCoordinate};
            break;
    }
}

MovableView::MovableView(Position initialPosition) :
    currentPosition{initialPosition}{
}

Position MovableView::GetPositionInWindow() const {
    return {
        .xCoordinate = GameWindow::MARGIN + currentPosition.xCoordinate*GameWindow::GRID_SIDE-4,
        .yCoordinate = GameWindow::MARGIN + currentPosition.yCoordinate*GameWindow::GRID_SIDE-4
    };
}