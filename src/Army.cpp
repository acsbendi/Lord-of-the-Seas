#include "Army.h"
#include "Map.h"
#include <iostream>
Army::Army(Player& player) : Movable(player)
{

}

void Army::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    sf::RectangleShape rect(sf::Vector2f(6,6));
    rect.setPosition(Map::MARGIN + currentLocation->getCoordinates().x*Map::GRID_SIDE-3,
                       Map::MARGIN + currentLocation->getCoordinates().y*Map::GRID_SIDE-3);
    rect.setFillColor(owner.getColor());
    target.draw(rect);
}

bool Army::move(Direction direction) {
    std::cout << "army move";
    GridPoint* destination = currentLocation->getPointNeighbor(direction);
    if(destination && destination->enter(this)){
        setEdgeOwners(direction);
        currentLocation->exit(this);
        currentLocation = destination;
        return true;
    } else
        return false;
}
