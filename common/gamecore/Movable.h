#ifndef MOVABLE_H
#define MOVABLE_H

#include <vector>
#include <memory>
#include "../utils/Enums.h"

using std::vector;

class GridPoint;
class Player;
class IMovableObserver;
class PlayerProxy;

class Movable {
public:
    explicit Movable(Player&);
    virtual ~Movable() = default;
    GridPoint* GetCurrentLocation() const;
    PlayerProxy getOwner() const;
    void SetCurrentLocation(GridPoint*);
    void SetEdgeOwners(Direction);
    void Attach(IMovableObserver* observer);
    void Detach(IMovableObserver* observer);
    virtual void Move(Direction) = 0;

protected:
    void NotifyOnSuccessfulMove(Direction directionOfMove) const;

    GridPoint* currentLocation;
    Player& owner;

private:
    void SetOwnerInNeighborIfExists(IntermediateDirection, Direction);

    vector<IMovableObserver*> observers;
};

#endif // MOVABLE_H
