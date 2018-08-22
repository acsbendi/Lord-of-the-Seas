//
// Created by Bendi on 1/28/2018.
//

#include "Land.h"
#include "Graphics.h"

const Texture Land::texture = Graphics::CreateTexture("land.png");

Land::Land(int x, int y) : GridSquare{x,y} { }

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

const Texture& Land::GetTexture() const {
    return texture;
}