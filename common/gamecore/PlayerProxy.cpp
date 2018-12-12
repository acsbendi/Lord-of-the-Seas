//
// Created by acsbendi on 2018.10.04..
//

#include "PlayerProxy.h"


bool PlayerProxy::operator==(const PlayerProxy& other) const {
    return this->representedPlayer == other.representedPlayer;
}

PlayerProxy::PlayerProxy(const Player* const representedPlayer) :
    representedPlayer{representedPlayer} {}