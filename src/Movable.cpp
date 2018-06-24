#include "Movable.h"
#include "GridSquare.h"

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
                if(currentLocation->getSquareNeighbor(northwest))
                    currentLocation->getSquareNeighbor(northwest)->setEdgeOwner(right,&owner);
                if(currentLocation->getSquareNeighbor(northeast) )
                    currentLocation->getSquareNeighbor(northeast)->setEdgeOwner(left,&owner);
                break;
            case down:
                if(currentLocation->getSquareNeighbor(southwest))
                    currentLocation->getSquareNeighbor(southwest)->setEdgeOwner(right,&owner);
                if(currentLocation->getSquareNeighbor(southeast) )
                    currentLocation->getSquareNeighbor(southeast)->setEdgeOwner(left,&owner);
                break;
            case left:
                if(currentLocation->getSquareNeighbor(northwest))
                    currentLocation->getSquareNeighbor(northwest)->setEdgeOwner(down,&owner);
                if(currentLocation->getSquareNeighbor(southwest) )
                    currentLocation->getSquareNeighbor(southwest)->setEdgeOwner(up,&owner);
                break;

            case right:
                if(currentLocation->getSquareNeighbor(northeast))
                    currentLocation->getSquareNeighbor(northeast)->setEdgeOwner(down,&owner);
                if(currentLocation->getSquareNeighbor(southeast) )
                    currentLocation->getSquareNeighbor(southeast)->setEdgeOwner(up,&owner);
                break;
        }
}

