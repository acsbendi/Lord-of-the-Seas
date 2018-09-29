//
// Created by Bendi on 9/3/2018.
//

#include "LandView.hpp"
#include "../../../common/utils/graphics/Graphics.h"


const Texture LandView::texture = Graphics::CreateTexture("land.png");

LandView::LandView(int x, int y, const GridSquare& gridSquare) : GridSquareView{x, y, gridSquare} { }

const Texture& LandView::GetTexture() const {
    return texture;
}