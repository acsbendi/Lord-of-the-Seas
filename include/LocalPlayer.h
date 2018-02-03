//
// Created by Bendi on 1/31/2018.
//

#ifndef LORD_OF_THE_SEAS_LOCALPLAYER_H
#define LORD_OF_THE_SEAS_LOCALPLAYER_H

#include "Player.h"
#include "ILocalPlayerObserver.h"

class LocalPlayer : public Player {
private:
    std::vector<ILocalPlayerObserver *> localPlayerobservers;

    void notifyOnMove(Direction direction) const override;

    void notifyOnConfirmation(bool confirmed) const;

    void confirmed() override;

    void unconfirmed() override;
public:
    LocalPlayer(sf::Color color, const std::string &name);

    void attachLocalPlayerObserver(ILocalPlayerObserver *observer);

    void detachLocalPlayerObserver(ILocalPlayerObserver* observer);
};


#endif //LORD_OF_THE_SEAS_LOCALPLAYER_H
