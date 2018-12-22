//
// Created by Bendi on 9/4/2018.
//
#include <SFML/Graphics/CircleShape.hpp>
#include "../../../common/gamecore/Ship.h"
#include "ShipView.hpp"
#include "../../../common/gamecore/Player.h"

using sf::CircleShape;

ShipView::ShipView(Position initialPosition, shared_ptr<PlayerView> playerView, PlayerProxy owner) :
    MovableView{initialPosition, move(playerView), owner} {
}

void ShipView::draw(RenderTarget& target, RenderStates) const
{
    Position positionInWindow = GetPositionInWindow();

    CircleShape circle(4);
    circle.setPosition(positionInWindow.xCoordinate, positionInWindow.yCoordinate);
    circle.setFillColor(GetColor());
    target.draw(circle);
}

void ShipView::OnMove(Direction moveDirection) {
    ChangePositionOnMove(moveDirection);
}
