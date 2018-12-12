//
// Created by Bendi on 9/4/2018.
//

#ifndef LORD_OF_THE_SEAS_MOVABLEVIEW_HPP
#define LORD_OF_THE_SEAS_MOVABLEVIEW_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <memory>
#include <SFML/Graphics/Color.hpp>
#include "../../../common/gamecore/IMovableObserver.hpp"
#include "../../../common/gamecore/Position.hpp"
#include "../../../common/gamecore/PlayerProxy.h"

using std::unique_ptr;
using std::shared_ptr;
using sf::Drawable;
using sf::Vector2i;
using sf::Color;

class PlayerView;
class ArmyView;

class MovableView : public Drawable, public IMovableObserver{
public:
    unique_ptr<ArmyView> CreateLandedArmyView(Direction direction) const;

protected:
    explicit MovableView(Position initialPosition, shared_ptr<PlayerView> playerView, PlayerProxy owner);

    void ChangePositionOnMove(Direction directionOfMove);
    Position GetPositionInWindow() const;
    Color GetColor() const;

private:
    Position currentPosition;
    shared_ptr<PlayerView> playerView;
    PlayerProxy owner;
};


#endif //LORD_OF_THE_SEAS_MOVABLEVIEW_HPP
