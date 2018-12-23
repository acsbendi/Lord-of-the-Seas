//
// Created by Bendi on 9/3/2018.
//

#include "LandView.hpp"
#include "../../../common/utils/graphics/Graphics.h"
#include "../../../common/utils/graphics/ResourceManager.hpp"


const int LandView::textureToken = Graphics::CreateTexture("land.png");

LandView::LandView(Position position, shared_ptr<PlayerView> playerView) :
GridSquareView{position, move(playerView)} { }

const Texture& LandView::GetTexture() const {
    return ResourceManager::GetInstance().GetTexture(textureToken);
}