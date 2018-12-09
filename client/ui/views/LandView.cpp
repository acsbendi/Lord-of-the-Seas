//
// Created by Bendi on 9/3/2018.
//

#include "LandView.hpp"
#include "../../../common/utils/graphics/Graphics.h"


const Texture LandView::texture = Graphics::CreateTexture("land.png");

LandView::LandView(Position position, shared_ptr<PlayerView> playerView) :
GridSquareView{position, move(playerView)} { }

const Texture& LandView::GetTexture() const {
    return texture;
}