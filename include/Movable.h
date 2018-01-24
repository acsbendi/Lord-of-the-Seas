#ifndef MOVABLE_H
#define MOVABLE_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "Enums.h"

class GridPoint;

class Player;

class Movable : public sf::Drawable
{
    public:
        explicit Movable(Player&);
        ~Movable() override = default;
        GridPoint* getCurrentLocation() const;
        void setCurrentLocation(GridPoint*);
        bool setEdgeOwners(Direction);
        virtual bool move(Direction) = 0;

    protected:
        GridPoint* currentLocation;
        Player& owner;

    private:

};

#endif // MOVABLE_H
