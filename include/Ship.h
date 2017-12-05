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
        std::shared_ptr<Army> getArmyOnBoard() const;
        void setArmyOnBoard(const std::shared_ptr<Army>&);
        void draw(sf::RenderTarget&, sf::RenderStates) const override;
        virtual ~Ship();

    protected:

    private:
        std::shared_ptr<Army> armyOnBoard;

};

#endif // SHIP_H
