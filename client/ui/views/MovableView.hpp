//
// Created by Bendi on 9/4/2018.
//

#ifndef LORD_OF_THE_SEAS_MOVABLEVIEW_HPP
#define LORD_OF_THE_SEAS_MOVABLEVIEW_HPP

#include <SFML/Graphics/Drawable.hpp>
#include "../../common/gamecore/IMovableObserver.hpp"

using sf::Drawable;
using sf::Vector2i;

class MovableView : public Drawable, public IMovableObserver{
public:
    void SetCoordinates(Vector2i coordinates);

protected:
    void ChangePositionOnMove(Direction directionOfMove);

    Vector2i currentPosition;
};


#endif //LORD_OF_THE_SEAS_MOVABLEVIEW_HPP
