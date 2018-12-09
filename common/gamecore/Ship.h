#ifndef SHIP_H
#define SHIP_H

#include <memory>
#include "GridPoint.h"
#include "Army.h"

class Army;
class GridPoint;

class Ship : public Movable {
public:
    explicit Ship(Player& player);
    const Army* GetArmyOnBoard() const;
    void SetArmyOnBoard(const Army *);
    /*!
     * Makes the ship move in a specified direction
     * @return Returns whether the movement was successful.
     */
    void Move(Direction) override;
    bool IsAtCoast() const;

private:
    const Army* armyOnBoard;
};

#endif // SHIP_H
