#include "Player.h"

Player::Player(const sf::Color color) : color{color}, score{0}
{
    ship = std::unique_ptr<Ship>{new Ship{*this}};
    army = std::unique_ptr<Army>{new Army{*this}};
    ship->setArmyOnBoard(army.get());
}

Ship* Player::getShip() const
{
    return ship.get();
}

void Player::setShip(std::unique_ptr<Ship> ship)
{
    this->ship = std::move(ship);
}

Army* Player::getArmy() const
{
    return army.get();
}

void Player::setArmy(std::unique_ptr<Army> army)
{
    this->army = std::move(army);
}

sf::Color Player::getColor() const
{
    return color;
}

int Player::getScore() const
{
    return score;
}

void Player::setScore(int score)
{
    this->score = score;
}
