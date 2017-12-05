#include "Army.h"
#include "Map.h"

Army::Army(const Player& player) : Movable(player)
{

}

void Army::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape rect(sf::Vector2f(6,6));
    rect.setPosition(Map::MARGIN + currentLocation->getGridSquare().getCoordinates().x*Map::GRID_SIDE-3,
                       Map::MARGIN + currentLocation->getGridSquare().getCoordinates().y*Map::GRID_SIDE-3);
    rect.setFillColor(owner.getColor());
    target.draw(rect);
}

Army::~Army()
{
    //dtor
}
