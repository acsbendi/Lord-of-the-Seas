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

bool Movable::SetEdgeOwners(Direction direction) {
        switch(direction){
            case up:
                if(currentLocation->GetSquareNeighbor(northwest))
                    currentLocation->GetSquareNeighbor(northwest)->SetEdgeOwner(right, &owner);
                if(currentLocation->GetSquareNeighbor(northeast) )
                    currentLocation->GetSquareNeighbor(northeast)->SetEdgeOwner(left, &owner);
                break;
            case down:
                if(currentLocation->GetSquareNeighbor(southwest))
                    currentLocation->GetSquareNeighbor(southwest)->SetEdgeOwner(right, &owner);
                if(currentLocation->GetSquareNeighbor(southeast) )
                    currentLocation->GetSquareNeighbor(southeast)->SetEdgeOwner(left, &owner);
                break;
            case left:
                if(currentLocation->GetSquareNeighbor(northwest))
                    currentLocation->GetSquareNeighbor(northwest)->SetEdgeOwner(down, &owner);
                if(currentLocation->GetSquareNeighbor(southwest) )
                    currentLocation->GetSquareNeighbor(southwest)->SetEdgeOwner(up, &owner);
                break;

            case right:
                if(currentLocation->GetSquareNeighbor(northeast))
                    currentLocation->GetSquareNeighbor(northeast)->SetEdgeOwner(down, &owner);
                if(currentLocation->GetSquareNeighbor(southeast) )
                    currentLocation->GetSquareNeighbor(southeast)->SetEdgeOwner(up, &owner);
                break;
        }
}

