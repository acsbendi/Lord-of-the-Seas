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
        explicit Player(const sf::Color);
        virtual ~Player() = default;
        Ship* getShip() const;
        void setShip(std::unique_ptr<Ship>);
        Army* getArmy() const;
        void setArmy(std::unique_ptr<Army>);
        sf::Color getColor() const;
        int getScore() const;
        void setScore(int);

    protected:

    private:
        static int MAX_NUMBER_OF_MOVES;

        std::unique_ptr<Ship> ship;
        std::unique_ptr<Army> army;
        const sf::Color color;
        int score;

};

#endif // PLAYER_H
