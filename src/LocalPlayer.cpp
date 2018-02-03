//
// Created by Bendi on 1/31/2018.
//

#include "LocalPlayer.h"

LocalPlayer::LocalPlayer(sf::Color color, const std::string &name) : Player{color,name}{

}

void LocalPlayer::attachLocalPlayerObserver(ILocalPlayerObserver* observer){
    localPlayerobservers.push_back(observer);
}

void LocalPlayer::detachLocalPlayerObserver(ILocalPlayerObserver* observer){
    localPlayerobservers.erase(std::remove(localPlayerobservers.begin(),localPlayerobservers.end(),observer),localPlayerobservers.end());
}

void LocalPlayer::notifyOnMove(Direction direction) const{
    for(ILocalPlayerObserver* observer : localPlayerobservers)
        observer->onMove(direction);
    for(IPlayerObserver* observer : observers)
        observer->onMove();
}

void LocalPlayer::notifyOnConfirmation(bool confirmed) const{
    for(ILocalPlayerObserver* observer : localPlayerobservers)
        observer->onConfirmation(confirmed);
}

void LocalPlayer::confirmed(){
    notifyOnConfirmation(true);
    landingAccepted();
}

void LocalPlayer::unconfirmed(){
    notifyOnConfirmation(false);
    landingAccepted();
}
