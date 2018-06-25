//
// Created by Bendi on 1/28/2018.
//

#include "Water.h"
#include "Graphics.h"
#include "GameWindow.h"

sf::Texture Water::texture = Graphics::CreateTexture("water.png");

Water::Water(int x, int y) : GridSquare{x,y} { }

void Water::draw(sf::RenderTarget & target, sf::RenderStates) const {

    /*drawing the texture*/
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(GameWindow::MARGIN + coordinates.x*GameWindow::GRID_SIDE,GameWindow::MARGIN + coordinates.y*GameWindow::GRID_SIDE);
    target.draw(sprite);

    DrawGridSquare(target);
}

int Water::GetValue() const {
    return 1;
}

bool Water::IsSea() const {
    return true;
}

bool Water::IsLand() const {
    return false;
}

bool Water::CanEnd() const{
    return true;
}