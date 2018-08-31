#include "Movable.h"
#include "GridSquare.h"
#include "GridPoint.h"

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

bool Movable::SetEdgeOwners(Direction directionOfMove) {
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

