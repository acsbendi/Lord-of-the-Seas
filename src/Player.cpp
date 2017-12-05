#include "Player.h"

Player::Player(const sf::Color color) : color{color}
{
    ship = std::make_shared<Ship>(*this);
    army = nullptr;
}

Player::~Player()
{
    //dtor
}

std::shared_ptr<Ship> Player::getShip() const
{
    return ship;
}

void Player::setShip(std::shared_ptr<Ship>& ship)
{
    this->ship = ship;
}

std::shared_ptr<Army> Player::getArmy() const
{
    return army;
}

void Player::setArmy(const std::shared_ptr<Army>& army)
{
    this->army = army;
}

sf::Color Player::getColor() const
{
    return color;
}
