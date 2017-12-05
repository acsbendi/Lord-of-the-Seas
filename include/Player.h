#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Army.h"
#include "Enums.h"
#include "Map.h"

class Map;

class Player
{
    public:
        Player(const sf::Color);
        virtual ~Player();
        void move(Map&);
        std::shared_ptr<Ship> getShip() const;
        void setShip(std::shared_ptr<Ship>&);
        std::shared_ptr<Army> getArmy() const;
        void setArmy(const std::shared_ptr<Army>&);
        sf::Color getColor() const;

    protected:

    private:
        static int MAX_NUMBER_OF_MOVES;

        std::shared_ptr<Ship> ship;
        std::shared_ptr<Army> army;
        const sf::Color color;

};

#endif // PLAYER_H
