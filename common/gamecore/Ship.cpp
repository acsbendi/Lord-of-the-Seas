#include "Ship.h"
#include "Map.h"

const Army* Ship::GetArmyOnBoard() const
{
    return armyOnBoard;
}


void Ship::SetArmyOnBoard(const Army *army)
{
    armyOnBoard = army;
}

void Ship::Move(Direction direction) {
    GridPoint* destination = currentLocation->GetPointNeighbor(direction);
    if(destination && destination->Enter(this)){
        SetEdgeOwners(direction);
        currentLocation->Exit(this);
        currentLocation = destination;
        NotifyOnSuccessfulMove(direction);
    }
}

Ship::Ship(Player& player) : Movable(player)
{

}

bool Ship::IsAtCoast() const{
    return  (currentLocation->GetPointNeighbor(left) && currentLocation->GetPointNeighbor(left)->IsLand()) ||
            (currentLocation->GetPointNeighbor(right) && currentLocation->GetPointNeighbor(right)->IsLand()) ||
            (currentLocation->GetPointNeighbor(up) && currentLocation->GetPointNeighbor(up)->IsLand()) ||
            (currentLocation->GetPointNeighbor(down) && currentLocation->GetPointNeighbor(down)->IsLand());
}