#include "Ship.h"
#include "Map.h"
#include "GameWindow.h"

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
    circle.setPosition(GameWindow::MARGIN + currentLocation->getCoordinates().x*GameWindow::GRID_SIDE-4,
                       GameWindow::MARGIN + currentLocation->getCoordinates().y*GameWindow::GRID_SIDE-4);
    circle.setFillColor(owner.GetColor());
    target.draw(circle);
}

bool Ship::Move(Direction direction) {
    GridPoint* destination = currentLocation->getPointNeighbor(direction);
    if(destination && destination->enter(this)){
        SetEdgeOwners(direction);
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