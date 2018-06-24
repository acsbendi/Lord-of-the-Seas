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
        explicit Ship(Player& player);
        const Army* getArmyOnBoard() const;
        void setArmyOnBoard(const Army*);
        void draw(sf::RenderTarget&, sf::RenderStates) const override;
    /*!
     * Makes the ship move in a specified direction
     * @return Returns whether the movement was successful.
     */
        bool Move(Direction) override;
        bool isAtCoast() const;

    protected:

    private:
        const Army* armyOnBoard;
};

#endif // SHIP_H
