#ifndef ARMY_H
#define ARMY_H

#include <memory>
#include "Movable.h"
#include "GridPoint.h"

class GridPoint;
class Player;
class ArmyView;

class Army : public Movable {
public:
    explicit Army(Player&);
    bool Move(Direction) override ;

private:
    friend class ArmyView;
};

#endif // ARMY_H
