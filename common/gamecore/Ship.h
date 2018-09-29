#ifndef SHIP_H
#define SHIP_H

#include <memory>
#include "GridPoint.h"
#include "Army.h"

class Army;
class GridPoint;
class Shipview;

class Ship : public Movable {
public:
    explicit Ship(Player& player);
    const Army* GetArmyOnBoard() const;
    void SetArmyOnBoard(const Army *);
    /*!
     * Makes the ship move in a specified direction
     * @return Returns whether the movement was successful.
     */
    bool Move(Direction) override;
    bool IsAtCoast() const;

private:
    const Army* armyOnBoard;

    friend class ShipView;
};

#endif // SHIP_H