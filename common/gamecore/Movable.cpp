#include <algorithm>
#include "Movable.h"
#include "GridSquare.h"
#include "GridPoint.h"
#include "IMovableObserver.hpp"
#include "Player.h"

using std::remove;

Movable::Movable(Player& player) : currentLocation{nullptr}, owner{player}
{

}

GridPoint* Movable::GetCurrentLocation() const
{
    return currentLocation;
}

void Movable::SetCurrentLocation(GridPoint *cl)
{
    currentLocation = cl;
}

void Movable::SetEdgeOwners(Direction directionOfMove) {
    switch (directionOfMove) {
        case up:
            SetOwnerInNeighborIfExists(northwest, right);
            SetOwnerInNeighborIfExists(northeast, left);
            break;
        case down:
            SetOwnerInNeighborIfExists(southwest, right);
            SetOwnerInNeighborIfExists(southeast, left);
            break;
        case left:
            SetOwnerInNeighborIfExists(northwest, down);
            SetOwnerInNeighborIfExists(southwest, up);
            break;
        case right:
            SetOwnerInNeighborIfExists(northeast, down);
            SetOwnerInNeighborIfExists(southeast, up);
            break;
    }
}

void Movable::SetOwnerInNeighborIfExists(IntermediateDirection directionOfNeighbor, Direction directionOfEdge) {
    if (currentLocation->GetSquareNeighbor(directionOfNeighbor))
        currentLocation->GetSquareNeighbor(directionOfNeighbor)->SetEdgeOwner(directionOfEdge, &owner);
}

void Movable::Attach(IMovableObserver* observer, bool front){
    if(front)
        observers.insert(observers.begin(), observer);
    else
        observers.push_back(observer);
}

void Movable::Detach(IMovableObserver* observer){
    observers.erase(remove(observers.begin(),observers.end(),observer),observers.end());
}

void Movable::NotifyOnSuccessfulMove(Direction directionOfMove) const {
    for(IMovableObserver* observer : observers)
        observer->OnMove(directionOfMove);
}

PlayerProxy Movable::getOwner() const {
    return owner.CreateProxy();
}
