#include "Army.h"
#include "GameWindow.h"
#include "Player.h"

using sf::RectangleShape;
using sf::Vector2f;

Army::Army(Player& player) : Movable(player)
{

}

void Army::draw(RenderTarget& target, RenderStates) const
{
    RectangleShape rect(Vector2f(6,6));
    rect.setPosition(GameWindow::MARGIN + currentLocation->GetCoordinates().x*GameWindow::GRID_SIDE-3,
                     GameWindow::MARGIN + currentLocation->GetCoordinates().y*GameWindow::GRID_SIDE-3);
    rect.setFillColor(owner.GetColor());
    target.draw(rect);
}

bool Army::Move(Direction direction) {
    GridPoint* destination = currentLocation->GetPointNeighbor(direction);
    if(destination && destination->Enter(this)){
        SetEdgeOwners(direction);
        currentLocation->Exit(this);
        currentLocation = destination;
        return true;
    } else
        return false;
}
