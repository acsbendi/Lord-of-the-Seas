//
// Created by Bendi on 9/3/2018.
//

#include "LandView.hpp"
#include "../../../common/utils/graphics/Graphics.h"
#include "../../../common/utils/graphics/ResourceManager.hpp"


int LandView::textureToken = -1;

LandView::LandView(Position position, shared_ptr<PlayerView> playerView) :
GridSquareView{position, move(playerView)} {
    if(textureToken == -1){
        textureToken = Graphics::CreateTexture("land.png");
    }
}

const Texture& LandView::GetTexture() const {
    return ResourceManager::GetInstance().GetTexture(textureToken);
}