//
// Created by acsbendi on 2018.12.09..
//

#ifndef LORD_OF_THE_SEAS_PLAYERVIEW_HPP
#define LORD_OF_THE_SEAS_PLAYERVIEW_HPP

#include <SFML/Graphics/Color.hpp>
#include <unordered_map>
#include "../../common/gamecore/PlayerProxy.h"

using std::unordered_map;
using sf::Color;

class PlayerView {
private:
    const Color colors[2] = {Color::Red, Color::Magenta};
    unordered_map<PlayerProxy, Color> associations{};

public:
    Color GetColorFor(PlayerProxy player);
    void RegisterPlayer(PlayerProxy player);

};


#endif //LORD_OF_THE_SEAS_PLAYERVIEW_HPP
