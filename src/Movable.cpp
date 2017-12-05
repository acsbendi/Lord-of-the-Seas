#include "Movable.h"

Movable::Movable(const Player& player) : currentLocation{nullptr}, owner{player}
{

}

Movable::~Movable()
{

}

std::shared_ptr<GridPoint> Movable::getCurrentLocation()
{
    return currentLocation;
}

void Movable::setCurrentLocation(std::shared_ptr<GridPoint>& cl)
{
    currentLocation = cl;
}

const Player& Movable::getOwner() const
{
    return owner;
}

