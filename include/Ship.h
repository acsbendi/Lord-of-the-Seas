#ifndef SHIP_H
#define SHIP_H

#include <memory>
#include "GridPoint.h"
#include "Army.h"

class Army;

class GridPoint;

class Ship : public Movable
{
    public:
        Ship(const Player& player);
        const Army* getArmyOnBoard() const;
        void setArmyOnBoard(const Army*);
        void draw(sf::RenderTarget&, sf::RenderStates) const override;
        virtual ~Ship() = default;

    protected:

    private:
        const Army* armyOnBoard;

};

#endif // SHIP_H
