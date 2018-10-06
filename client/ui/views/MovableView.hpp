//
// Created by Bendi on 9/4/2018.
//

#ifndef LORD_OF_THE_SEAS_MOVABLEVIEW_HPP
#define LORD_OF_THE_SEAS_MOVABLEVIEW_HPP

#include <SFML/Graphics/Drawable.hpp>
#include "../../../common/gamecore/IMovableObserver.hpp"
#include "../../../common/gamecore/Position.hpp"

using sf::Drawable;
using sf::Vector2i;

class MovableView : public Drawable, public IMovableObserver{
protected:
    explicit MovableView(Position initialPosition);

    void ChangePositionOnMove(Direction directionOfMove);
    Position GetPositionInWindow() const;

private:
    Position currentPosition;
};


#endif //LORD_OF_THE_SEAS_MOVABLEVIEW_HPP
