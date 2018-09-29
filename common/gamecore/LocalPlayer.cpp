//
// Created by Bendi on 1/31/2018.
//

#include "LocalPlayer.h"
#include "ILocalPlayerObserver.h"

using std::remove;

LocalPlayer::LocalPlayer(Color color, const string &name) : Player{color,name}{

}

void LocalPlayer::AttachLocalPlayerObserver(ILocalPlayerObserver *observer){
    localPlayerobservers.push_back(observer);
}

void LocalPlayer::DetachLocalPlayerObserver(ILocalPlayerObserver *observer){
    localPlayerobservers.erase(remove(localPlayerobservers.begin(),localPlayerobservers.end(),observer),localPlayerobservers.end());
}

void LocalPlayer::NotifyOnMove(Direction direction) const{
    for(ILocalPlayerObserver* observer : localPlayerobservers)
        observer->OnMove(direction);
    for(IPlayerObserver* observer : observers)
        observer->OnMove();
}

void LocalPlayer::NotifyOnConfirmation(bool confirmed) const{
    for(ILocalPlayerObserver* observer : localPlayerobservers)
        observer->OnConfirmation(confirmed);
}

void LocalPlayer::Confirmed(){
    NotifyOnConfirmation(true);
    LandingAccepted();
}

void LocalPlayer::Unconfirmed(){
    NotifyOnConfirmation(false);
    LandingAccepted();
}
