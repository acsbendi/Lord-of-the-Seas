#ifndef MOVABLE_H
#define MOVABLE_H

#include <memory>
#include <SFML/Graphics.hpp>

class GridPoint;

class Player;

class Movable : public sf::Drawable
{
    public:
        explicit Movable(const Player&);
        virtual ~Movable() = default;
        GridPoint* getCurrentLocation() const;
        void setCurrentLocation(GridPoint*);
        const Player& getOwner() const;

    protected:
        GridPoint* currentLocation;
        const Player& owner;

    private:

};

#endif // MOVABLE_H
