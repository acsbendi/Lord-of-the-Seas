//
// Created by Bendi on 1/28/2018.
//

#include "Land.h"

sf::Texture Land::texture = GridSquare::createTexture("land.png");

Land::Land(int x, int y) : GridSquare{x,y} { }

void Land::draw(sf::RenderTarget & target, sf::RenderStates) const {

    /*drawing the texture*/
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(Map::MARGIN + coordinates.x*Map::GRID_SIDE,Map::MARGIN + coordinates.y*Map::GRID_SIDE);
    target.draw(sprite);

    drawGridSquare(target);
}

int Land::getValue() const {
    return 5;
}

bool Land::isSea() const {
    return false;
}

bool Land::isLand() const {
    return true;
}

bool Land::canEnd() const{
    return true;
}
