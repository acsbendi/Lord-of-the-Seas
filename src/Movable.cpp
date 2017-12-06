#include "Movable.h"

Movable::Movable(const Player& player) : currentLocation{nullptr}, owner{player}
{

}

Movable::~Movable()
{

}

GridPoint* Movable::getCurrentLocation() const
{
    return currentLocation;
}

void Movable::setCurrentLocation(GridPoint* cl)
{
    currentLocation = cl;
}

const Player& Movable::getOwner() const
{
    return owner;
}

