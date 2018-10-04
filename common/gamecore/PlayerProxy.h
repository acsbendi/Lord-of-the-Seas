//
// Created by acsbendi on 2018.10.04..
//

#ifndef LORD_OF_THE_SEAS_PLAYERPROXY_H
#define LORD_OF_THE_SEAS_PLAYERPROXY_H

class Player;

class PlayerProxy {
public:
    bool operator==(const PlayerProxy& other) const;

private:
    explicit PlayerProxy(const Player* representedPlayer);

    const Player* const representedPlayer;

    friend class Player;
};


#endif //LORD_OF_THE_SEAS_PLAYERPROXY_H
