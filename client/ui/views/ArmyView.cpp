//
// Created by Bendi on 9/4/2018.
//

#include "ArmyView.hpp"
#include "../GameWindow.h"
#include "../../../common/gamecore/Army.h"
#include "../../../common/gamecore/Player.h"

using sf::RectangleShape;
using sf::Vector2f;


ArmyView::ArmyView(Position initialPosition, shared_ptr<PlayerView> playerView, PlayerProxy owner) :
        MovableView{initialPosition, move(playerView), owner} {
}

void ArmyView::draw(RenderTarget& target, RenderStates) const
{
    Position positionInWindow = GetPositionInWindow();

    RectangleShape rect(Vector2f(6,6));
    rect.setPosition(positionInWindow.xCoordinate, positionInWindow.yCoordinate);
    rect.setFillColor(GetColor());
    target.draw(rect);
}

void ArmyView::OnMove(Direction moveDirection) {
    ChangePositionOnMove(moveDirection);
}