//
// Created by Bendi on 1/28/2018.
//

#include "Water.h"


sf::Texture Water::texture = GridSquare::createTexture("water.png");

Water::Water(int x, int y) : GridSquare{x,y} { }

void Water::draw(sf::RenderTarget & target, sf::RenderStates) const {

    /*drawing the texture*/
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(Map::MARGIN + coordinates.x*Map::GRID_SIDE,Map::MARGIN + coordinates.y*Map::GRID_SIDE);
    target.draw(sprite);

    drawGridSquare(target);
}

int Water::getValue() const {
    return 1;
}

bool Water::isSea() const {
    return true;
}

bool Water::isLand() const {
    return false;
}

bool Water::canEnd() const{
    return true;
}