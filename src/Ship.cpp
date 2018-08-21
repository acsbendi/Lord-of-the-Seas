#include "Ship.h"
#include "Map.h"
#include "GameWindow.h"

using sf::CircleShape;

const Army* Ship::GetArmyOnBoard() const
{
    return armyOnBoard;
}


void Ship::SetArmyOnBoard(const Army *army)
{
    armyOnBoard = army;
}

void Ship::draw(RenderTarget& target, RenderStates) const
{
    CircleShape circle(4);
    circle.setPosition(GameWindow::MARGIN + currentLocation->GetCoordinates().x*GameWindow::GRID_SIDE-4,
                       GameWindow::MARGIN + currentLocation->GetCoordinates().y*GameWindow::GRID_SIDE-4);
    circle.setFillColor(owner.GetColor());
    target.draw(circle);
}

bool Ship::Move(Direction direction) {
    GridPoint* destination = currentLocation->GetPointNeighbor(direction);
    if(destination && destination->Enter(this)){
        SetEdgeOwners(direction);
        currentLocation->Exit(this);
        currentLocation = destination;
        return true;
    } else
        return false;
}

Ship::Ship(Player& player) : Movable(player)
{

}

bool Ship::IsAtCoast() const{
    return currentLocation->GetPointNeighbor(left) && currentLocation->GetPointNeighbor(left)->IsLand() ||
            currentLocation->GetPointNeighbor(right) && currentLocation->GetPointNeighbor(right)->IsLand() ||
            currentLocation->GetPointNeighbor(up) && currentLocation->GetPointNeighbor(up)->IsLand() ||
            currentLocation->GetPointNeighbor(down) && currentLocation->GetPointNeighbor(down)->IsLand();
}