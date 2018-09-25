//
// Created by Bendi on 9/4/2018.
//

#include "ArmyView.hpp"
#include "GameWindow.h"
#include "Army.h"
#include "Player.h"

using sf::RectangleShape;
using sf::Vector2f;

ArmyView::ArmyView(Army& army) : army{army} {
}

void ArmyView::draw(RenderTarget& target, RenderStates) const
{
    RectangleShape rect(Vector2f(6,6));
    rect.setPosition(GameWindow::MARGIN + currentPosition.x*GameWindow::GRID_SIDE-3,
                     GameWindow::MARGIN + currentPosition.y*GameWindow::GRID_SIDE-3);
    rect.setFillColor(army.owner.GetColor());
    target.draw(rect);
}