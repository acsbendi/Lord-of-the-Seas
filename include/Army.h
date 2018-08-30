#ifndef ARMY_H
#define ARMY_H

#include <memory>
#include "Movable.h"
#include "GridPoint.h"

using sf::RenderTarget;
using sf::RenderStates;

class GridPoint;

class Player;

class Army : public Movable {
public:
    explicit Army(Player&);
    void draw(RenderTarget&, RenderStates) const override;
    bool Move(Direction) override ;
};

#endif // ARMY_H
