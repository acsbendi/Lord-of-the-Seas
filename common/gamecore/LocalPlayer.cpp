//
// Created by Bendi on 1/31/2018.
//

#include "LocalPlayer.h"
#include "ILocalPlayerObserver.h"

using std::remove;

LocalPlayer::LocalPlayer(const string &name) : Player{name}{

}

void LocalPlayer::AttachLocalPlayerObserver(ILocalPlayerObserver *observer){
    localPlayerObservers.push_back(observer);
}

void LocalPlayer::DetachLocalPlayerObserver(ILocalPlayerObserver *observer){
    localPlayerObservers.erase(remove(localPlayerObservers.begin(),localPlayerObservers.end(),observer),localPlayerObservers.end());
}

void LocalPlayer::NotifyOnMove(Direction direction) const{
    for(ILocalPlayerObserver* observer : localPlayerObservers)
        observer->OnMove(direction);
    for(IPlayerObserver* observer : observers)
        observer->OnMove();
}

void LocalPlayer::NotifyOnConfirmation(bool confirmed) const{
    for(ILocalPlayerObserver* observer : localPlayerObservers)
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
