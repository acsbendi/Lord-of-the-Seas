#ifndef MOVABLE_H
#define MOVABLE_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "Enums.h"

using sf::Drawable;

class GridPoint;
class Player;

class Movable : public Drawable {
public:
    explicit Movable(Player&);
    ~Movable() override = default;
    GridPoint* GetCurrentLocation() const;
    void SetCurrentLocation(GridPoint*);
    bool SetEdgeOwners(Direction);
    virtual bool Move(Direction) = 0;

protected:
    GridPoint* currentLocation;
    Player& owner;
};

#endif // MOVABLE_H
