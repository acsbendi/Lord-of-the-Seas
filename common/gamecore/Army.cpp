
#include "Army.h"
#include "Player.h"

using sf::RectangleShape;
using sf::Vector2f;

Army::Army(Player& player) : Movable(player)
{

}

void Army::Move(Direction direction) {
    GridPoint* destination = currentLocation->GetPointNeighbor(direction);
    if(destination && destination->Enter(this, direction)){
        OnSuccessfulMove(direction, destination);
    }
}

void Army::Land(Direction direction){
    GridPoint* destination = currentLocation->GetPointNeighbor(direction);
    if(destination && destination->Land(this)){
        OnSuccessfulMove(direction, destination);
    }
}

void Army::OnSuccessfulMove(Direction moveDirection, GridPoint* destination) {
    SetEdgeOwners(moveDirection);
    currentLocation->Exit(this);
    currentLocation = destination;
    NotifyOnSuccessfulMove(moveDirection);
}
