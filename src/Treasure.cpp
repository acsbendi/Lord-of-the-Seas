//
// Created by Bendi on 1/28/2018.
//

#include "Treasure.h"
#include "Graphics.h"
#include "GameWindow.h"

const sf::Texture Treasure::texture = Graphics::createTexture("treasure.png");

Treasure::Treasure(int x, int y) : GridSquare{x,y} { }

void Treasure::draw(sf::RenderTarget & target, sf::RenderStates) const {

    /*drawing the texture*/
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(GameWindow::MARGIN + coordinates.x*GameWindow::GRID_SIDE,GameWindow::MARGIN + coordinates.y*GameWindow::GRID_SIDE);
    target.draw(sprite);

    drawGridSquare(target);
}

int Treasure::GetValue() const {
    return 20;
}

bool Treasure::IsSea() const {
    return false;
}

bool Treasure::IsLand() const {
    return true;
}

bool Treasure::CanEnd() const{
    std::unordered_set<const GridSquare*> unordered_set;
    return getOwner(unordered_set) != nullptr;
}
