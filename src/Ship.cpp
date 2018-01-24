#include "Ship.h"
#include "Map.h"

const Army* Ship::getArmyOnBoard() const
{
    return armyOnBoard;
}


void Ship::setArmyOnBoard(const Army* army)
{
    armyOnBoard = army;
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    sf::CircleShape circle(4);
    circle.setPosition(Map::MARGIN + currentLocation->getCoordinates().x*Map::GRID_SIDE-4,
                       Map::MARGIN + currentLocation->getCoordinates().y*Map::GRID_SIDE-4);
    circle.setFillColor(owner.getColor());
    target.draw(circle);
}

bool Ship::move(Direction direction) {
    GridPoint* destination = currentLocation->getPointNeighbor(direction);
    if(destination && destination->enter(this)){
        setEdgeOwners(direction);
        currentLocation->exit(this);
        currentLocation = destination;
        return true;
    } else
        return false;
}

Ship::Ship(Player& player) : Movable(player)
{

}

bool Ship::isAtCoast() const{
    return  currentLocation->getPointNeighbor(left) && currentLocation->getPointNeighbor(left)->isLand() ||
            currentLocation->getPointNeighbor(right) &&currentLocation->getPointNeighbor(right)->isLand() ||
            currentLocation->getPointNeighbor(up) && currentLocation->getPointNeighbor(up)->isLand() ||
            currentLocation->getPointNeighbor(down) &&currentLocation->getPointNeighbor(down)->isLand();
}