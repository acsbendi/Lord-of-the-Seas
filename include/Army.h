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
        explicit Army(const Player&);
        void draw(sf::RenderTarget&, sf::RenderStates) const override;
        virtual ~Army() = default;

    protected:

    private:
};

#endif // ARMY_H
