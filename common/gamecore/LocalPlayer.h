//
// Created by Bendi on 1/31/2018.
//

#ifndef LORD_OF_THE_SEAS_LOCALPLAYER_H
#define LORD_OF_THE_SEAS_LOCALPLAYER_H

#include <SFML/Graphics/Color.hpp>
#include <string>
#include "Player.h"

using std::string;
using std::vector;
using sf::Color;

class ILocalPlayerObserver;

class LocalPlayer : public Player {
public:
    explicit LocalPlayer(const string &name);
    void AttachLocalPlayerObserver(ILocalPlayerObserver *observer);
    void DetachLocalPlayerObserver(ILocalPlayerObserver *observer);

private:
    vector<ILocalPlayerObserver *> localPlayerObservers;

    void NotifyOnMove(Direction direction) const override;
    void NotifyOnConfirmation(bool confirmed) const;
    void Confirmed() override;
    void Unconfirmed() override;
};


#endif //LORD_OF_THE_SEAS_LOCALPLAYER_H
