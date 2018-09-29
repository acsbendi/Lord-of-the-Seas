//
// Created by Bendi on 9/4/2018.
//
#include <SFML/Graphics/CircleShape.hpp>
#include "../../../common/gamecore/Ship.h"
#include "ShipView.hpp"
#include "../GameWindow.h"
#include "../../../common/gamecore/Player.h"

using sf::CircleShape;

ShipView::ShipView(Ship& ship) : ship{ship} {
}

void ShipView::draw(RenderTarget& target, RenderStates) const
{
    CircleShape circle(4);
    circle.setPosition(GameWindow::MARGIN + currentPosition.x*GameWindow::GRID_SIDE-4,
                       GameWindow::MARGIN + currentPosition.y*GameWindow::GRID_SIDE-4);
    circle.setFillColor(ship.owner.GetColor()); //TODO change this to a single dot solution
    target.draw(circle);
}

void ShipView::OnSuccessfulMove(Direction directionOfMove) {
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
