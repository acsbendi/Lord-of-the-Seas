//
// Created by acsbendi on 2018.10.04..
//

#ifndef LORD_OF_THE_SEAS_PLAYERPROXY_H
#define LORD_OF_THE_SEAS_PLAYERPROXY_H

#include <memory>

class Player;

class PlayerProxy {
public:
    bool operator==(const PlayerProxy& other) const;
    PlayerProxy(const PlayerProxy& other) = default;

private:
    explicit PlayerProxy(const Player* representedPlayer);

    const Player* representedPlayer;

    friend class Player;
    friend class std::hash<PlayerProxy>;
};

namespace std {

    template <>
    struct hash<PlayerProxy>
    {
        inline size_t operator()(const PlayerProxy& playerProxy) const
        {
            return hash<const Player*>()(playerProxy.representedPlayer);
        }
    };

}

#endif //LORD_OF_THE_SEAS_PLAYERPROXY_H
