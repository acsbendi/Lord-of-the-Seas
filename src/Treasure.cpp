//
// Created by Bendi on 1/28/2018.
//

#include "Treasure.h"
#include "Graphics.h"

const sf::Texture Treasure::texture = Graphics::createTexture("treasure.png");

Treasure::Treasure(int x, int y) : GridSquare{x,y} { }

void Treasure::draw(sf::RenderTarget & target, sf::RenderStates) const {

    /*drawing the texture*/
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(Map::MARGIN + coordinates.x*Map::GRID_SIDE,Map::MARGIN + coordinates.y*Map::GRID_SIDE);
    target.draw(sprite);

    drawGridSquare(target);
}

int Treasure::getValue() const {
    return 20;
}

bool Treasure::isSea() const {
    return false;
}

bool Treasure::isLand() const {
    return true;
}

bool Treasure::canEnd() const{
    std::unordered_set<const GridSquare*> unordered_set;
    return getOwner(unordered_set) != nullptr;
}
