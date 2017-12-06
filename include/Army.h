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
        Army(const Player&);
        void draw(sf::RenderTarget&, sf::RenderStates) const override;
        virtual ~Army();

    protected:

    private:
};

#endif // ARMY_H
