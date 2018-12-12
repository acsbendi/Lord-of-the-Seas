#include <SFML/Graphics/RectangleShape.hpp>
#include "Army.h"
#include "Player.h"

using sf::RectangleShape;
using sf::Vector2f;

Army::Army(Player& player) : Movable(player)
{

}

void Army::Move(Direction direction) {
    GridPoint* destination = currentLocation->GetPointNeighbor(direction);
    if(destination && destination->Enter(this)){
        SetEdgeOwners(direction);
        currentLocation->Exit(this);
        currentLocation = destination;
        NotifyOnSuccessfulMove(direction);
    }
}
