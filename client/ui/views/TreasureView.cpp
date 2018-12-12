//
// Created by Bendi on 9/3/2018.
//

#include "../../../common/utils/graphics/Graphics.h"
#include "../../../common/gamecore/GridSquare.h"
#include "TreasureView.hpp"


const Texture TreasureView::texture = Graphics::CreateTexture("treasure.png");

TreasureView::TreasureView(Position position, shared_ptr<PlayerView> playerView) :
GridSquareView{position, move(playerView)} { }

const Texture& TreasureView::GetTexture() const {
    return texture;
}