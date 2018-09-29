#ifndef MOVABLE_H
#define MOVABLE_H

#include <vector>
#include <memory>
#include "Enums.h"

using std::vector;

class GridPoint;
class Player;
class IMovableObserver;

class Movable {
public:
    explicit Movable(Player&);
    virtual ~Movable() = default;
    GridPoint* GetCurrentLocation() const;
    void SetCurrentLocation(GridPoint*);
    void SetEdgeOwners(Direction);
    void Attach(IMovableObserver* observer);
    void Detach(IMovableObserver* observer);
    virtual bool Move(Direction) = 0;

protected:
    void NotifyOnSuccessfulMove(Direction directionOfMove) const;

    GridPoint* currentLocation;
    Player& owner;

private:
    void SetOwnerInNeighborIfExists(IntermediateDirection, Direction);

    vector<IMovableObserver*> observers;
};

#endif // MOVABLE_H
