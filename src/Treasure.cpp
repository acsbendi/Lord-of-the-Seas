//
// Created by Bendi on 1/28/2018.
//

#include "Treasure.h"
#include "Graphics.h"
#include "GameWindow.h"

using std::unordered_set;
using sf::Sprite;

const Texture Treasure::texture = Graphics::CreateTexture("treasure.png");

Treasure::Treasure(int x, int y) : GridSquare{x,y} { }

void Treasure::draw(RenderTarget & target, RenderStates) const {

    /*drawing the texture*/
    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(GameWindow::MARGIN + coordinates.x*GameWindow::GRID_SIDE,GameWindow::MARGIN + coordinates.y*GameWindow::GRID_SIDE);
    target.draw(sprite);

    DrawGridSquare(target);
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
    unordered_set<const GridSquare*> unordered_set;
    return GetOwner(unordered_set) != nullptr;
}
