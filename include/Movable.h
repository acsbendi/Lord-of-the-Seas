#ifndef MOVABLE_H
#define MOVABLE_H

#include <memory>
#include <SFML/Graphics.hpp>

class GridPoint;

class Player;

class Movable : public sf::Drawable
{
    public:
        Movable(const Player&);
        virtual ~Movable();
        std::shared_ptr<GridPoint> getCurrentLocation();
        void setCurrentLocation(std::shared_ptr<GridPoint>&);
        const Player& getOwner() const;

    protected:
        std::shared_ptr<GridPoint> currentLocation;
        const Player& owner;

    private:

};

#endif // MOVABLE_H
