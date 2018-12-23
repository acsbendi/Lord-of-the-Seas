//
// Created by Bendi on 9/3/2018.
//

#include "TreasureView.hpp"
#include "../../../common/utils/graphics/ResourceManager.hpp"
#include "../../../common/utils/graphics/Graphics.h"


int TreasureView::textureToken = -1;

TreasureView::TreasureView(Position position, shared_ptr<PlayerView> playerView) :
GridSquareView{position, move(playerView)} {
    if(textureToken == -1){
        textureToken = Graphics::CreateTexture("treasure.png");
    }
}

const Texture& TreasureView::GetTexture() const {
    return ResourceManager::GetInstance().GetTexture(textureToken);
}