//
// Created by Bendi on 1/28/2018.
//

#include "Water.h"
#include "Graphics.h"

const Texture Water::texture = Graphics::CreateTexture("water.png");

Water::Water(int x, int y) : GridSquare{x,y} { }

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

const Texture& Water::GetTexture() const {
    return texture;
}