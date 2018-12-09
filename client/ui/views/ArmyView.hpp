//
// Created by Bendi on 9/4/2018.
//

#ifndef LORD_OF_THE_SEAS_ARMYVIEW_HPP
#define LORD_OF_THE_SEAS_ARMYVIEW_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "MovableView.hpp"

using sf::RenderTarget;
using sf::RenderStates;

class Army;

class ArmyView : MovableView{
public:
    explicit ArmyView(Position initialPosition, shared_ptr<PlayerView> playerView, PlayerProxy owner);
    void draw(RenderTarget&, RenderStates) const override;
    void OnMove(Direction moveDirection) override;
};


#endif //LORD_OF_THE_SEAS_ARMYVIEW_HPP
