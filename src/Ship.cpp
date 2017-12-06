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

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::CircleShape circle(4);
    circle.setPosition(Map::MARGIN + currentLocation->getGridSquare().getCoordinates().x*Map::GRID_SIDE-4,
                       Map::MARGIN + currentLocation->getGridSquare().getCoordinates().y*Map::GRID_SIDE-4);
    circle.setFillColor(owner.getColor());
    target.draw(circle);
}


Ship::Ship(const Player& player) : Movable(player)
{

}

Ship::~Ship()
{
    //dtor
}
