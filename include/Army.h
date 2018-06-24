#ifndef ARMY_H
#define ARMY_H

#include <memory>
#include "Movable.h"
#include "GridPoint.h"

class GridPoint;

class Player;

class Army : public Movable
{
    public:
        explicit Army(Player&);
        void draw(sf::RenderTarget&, sf::RenderStates) const override;
        bool Move(Direction) override ;

    protected:

    private:
};

#endif // ARMY_H
