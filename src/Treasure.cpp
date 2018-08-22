//
// Created by Bendi on 1/28/2018.
//

#include "Treasure.h"
#include "Graphics.h"

using std::unordered_set;

const Texture Treasure::texture = Graphics::CreateTexture("treasure.png");

Treasure::Treasure(int x, int y) : GridSquare{x,y} { }

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

const Texture& Treasure::GetTexture() const {
    return texture;
}
