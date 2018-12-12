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

private:
    friend class ArmyView;
};

#endif // ARMY_H
