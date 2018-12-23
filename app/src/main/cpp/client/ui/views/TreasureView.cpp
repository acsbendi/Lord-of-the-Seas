//
// Created by Bendi on 9/3/2018.
//

#include "TreasureView.hpp"
#include "../../../common/utils/graphics/ResourceManager.hpp"
#include "../../../common/utils/graphics/Graphics.h"


const int TreasureView::textureToken = Graphics::CreateTexture("treasure.png");

TreasureView::TreasureView(Position position, shared_ptr<PlayerView> playerView) :
GridSquareView{position, move(playerView)} { }

const Texture& TreasureView::GetTexture() const {
    return ResourceManager::GetInstance().GetTexture(textureToken);
}