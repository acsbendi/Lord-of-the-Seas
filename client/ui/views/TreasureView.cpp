//
// Created by Bendi on 9/3/2018.
//

#include "../client/GUI/TreasureView.hpp"
#include "../../../common/utils/graphics/Graphics.h"

const Texture TreasureView::texture = Graphics::CreateTexture("water.png");

TreasureView::TreasureView(int x, int y, const GridSquare& gridSquare) : GridSquareView{x, y, gridSquare} { }

const Texture& TreasureView::GetTexture() const {
    return texture;
}