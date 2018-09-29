//
// Created by Bendi on 9/3/2018.
//

#include "WaterView.hpp"
#include "../../../common/utils/graphics/Graphics.h"

const Texture WaterView::texture = Graphics::CreateTexture("water.png");

WaterView::WaterView(int x, int y, const GridSquare& gridSquare) : GridSquareView{x,y,gridSquare} { }

const Texture& WaterView::GetTexture() const {
    return texture;
}