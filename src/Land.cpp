//
// Created by Bendi on 1/28/2018.
//

#include "Land.h"
#include "Graphics.h"
#include "GameWindow.h"

sf::Texture Land::texture = Graphics::CreateTexture("land.png");

Land::Land(int x, int y) : GridSquare{x,y} { }

void Land::draw(sf::RenderTarget & target, sf::RenderStates) const {

    /*drawing the texture*/
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(GameWindow::MARGIN + coordinates.x*GameWindow::GRID_SIDE,
                       GameWindow::MARGIN + coordinates.y*GameWindow::GRID_SIDE);
    target.draw(sprite);

    DrawGridSquare(target);
}

int Land::GetValue() const {
    return 5;
}

bool Land::IsSea() const {
    return false;
}

bool Land::IsLand() const {
    return true;
}

bool Land::CanEnd() const{
    return true;
}
