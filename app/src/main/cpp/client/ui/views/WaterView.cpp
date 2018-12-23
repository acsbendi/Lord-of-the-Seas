//
// Created by Bendi on 9/3/2018.
//

#include "WaterView.hpp"
#include "../../../common/utils/graphics/Graphics.h"
#include "../../../common/utils/graphics/ResourceManager.hpp"


const int WaterView::textureToken = Graphics::CreateTexture("water.png");

WaterView::WaterView(Position position, shared_ptr<PlayerView> playerView) :
GridSquareView{position, move(playerView)} { }

const Texture& WaterView::GetTexture() const {
    return ResourceManager::GetInstance().GetTexture(textureToken);
}