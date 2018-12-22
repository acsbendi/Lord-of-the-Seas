//
// Created by acsbendi on 2018.12.09..
//

#include "PlayerView.hpp"

void PlayerView::RegisterPlayer(PlayerProxy player) {
    unsigned long size = associations.size();
    associations.insert({player, colors[size]});
}

Color PlayerView::GetColorFor(PlayerProxy player) {
    return associations.at(player);
}