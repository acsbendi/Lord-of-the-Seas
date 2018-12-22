#ifndef ARMY_H
#define ARMY_H

#include <memory>
#include "Movable.h"
#include "GridPoint.h"

class GridPoint;
class Player;

class Army : public Movable {
public:
    explicit Army(Player&);
    void Move(Direction) override ;
    void Land(Direction direction);

private:
    void OnSuccessfulMove(Direction moveDirection, GridPoint* destination);

    friend class ArmyView;
};

#endif // ARMY_H
