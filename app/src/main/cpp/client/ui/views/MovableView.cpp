//
// Created by Bendi on 9/9/2018.
//

#include <regex>
#include "../../../common/utils/Enums.h"
#include "MovableView.hpp"
#include "PlayerView.hpp"
#include "../GameWindow.h"
#include "ArmyView.hpp"

using std::make_unique;

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

MovableView::MovableView(Position initialPosition, shared_ptr<PlayerView> playerView, PlayerProxy owner) :
    currentPosition{initialPosition}, playerView{move(playerView)},
    owner{owner}{
}

Position MovableView::GetPositionInWindow() const {
    return {
        .xCoordinate = GameWindow::MARGIN + currentPosition.xCoordinate*GameWindow::GRID_SIDE-4,
        .yCoordinate = GameWindow::MARGIN + currentPosition.yCoordinate*GameWindow::GRID_SIDE-4
    };
}

Color MovableView::GetColor() const {
    return playerView->GetColorFor(owner);
}

unique_ptr<ArmyView> MovableView::CreateLandedArmyView(Direction direction) const {
    return make_unique<ArmyView>(currentPosition.NeighborPosition(direction), playerView, owner);
}