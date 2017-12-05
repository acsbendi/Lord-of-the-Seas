#include "Game.h"

#include <iostream>


int Game::NUMBER_OF_MOVES = 3;

Game::Game() : map{}
{
    player1 = std::make_shared<Player>(sf::Color::Red);
    player2 = std::make_shared<Player>(sf::Color::Magenta);
    map.initializeGrid(player1, player2);
    map.refresh();
}

Game::~Game()
{
    //dtor
}

Direction Game::getSelectedDirection()
{
    while(true)
    {
        sf::Keyboard::Key pressedKey = map.getPressedKey();
        switch(pressedKey)
        {
        case sf::Keyboard::Up:
            return up;
        case sf::Keyboard::Down:
            return down;
        case sf::Keyboard::Right:
            return right;
        case sf::Keyboard::Left:
            return left;
        default:
            continue;
        }
    }
}

bool Game::hasEnded() const
{
    return map.countGridSquares(GridSquareType::treasure) ==
           map.countGridSquares(GridSquareType::treasure, player1) +
           map.countGridSquares(GridSquareType::treasure, player2);
}

void Game::move(const std::shared_ptr<Player>& player)
{
    int countOfValidatedMoves = 0;
    while(countOfValidatedMoves < NUMBER_OF_MOVES)
    {
        Direction direction = getSelectedDirection();
        std::shared_ptr<GridPoint> destination;
        try
        {
            destination = map.getNeighbor(player->getShip()->getCurrentLocation().get(),direction);
            map.setEdgeOwner(player->getShip()->getCurrentLocation(),destination,player);
            player->getShip()->getCurrentLocation()->setMovable(nullptr);
            player->getShip()->setCurrentLocation(destination);
            destination->setMovable(player->getShip());
            if(!player->getArmy() && map.isLand(player->getShip()->getCurrentLocation())) landArmy(player);
            map.refresh();
            ++countOfValidatedMoves;
        }
        catch(std::out_of_range& e)
        {

        }
    }

    if(player->getArmy())
    {

    }
}

void Game::landArmy(const std::shared_ptr<Player>& player)
{
    sf::Keyboard::Key pressedKey = map.getPressedKey();
    if(pressedKey == sf::Keyboard::Return)
    {
        player->setArmy(player->getShip()->getArmyOnBoard());
        player->getShip()->setArmyOnBoard(nullptr);
        while(true)
        {
            Direction direction = getSelectedDirection();
            std::shared_ptr<GridPoint> destination;
            try
            {
                destination = map.getNeighbor(player->getShip()->getCurrentLocation().get(),direction);
                if(map.isLand(destination))
                {
                    destination->setMovable(player->getArmy());
                    player->getArmy()->setCurrentLocation(destination);
                    return;
                }
            }
            catch(std::out_of_range& e)
            {

            }
        }
    }
    else return;
}

void Game::playGame()
{
    while(!hasEnded())
    {
        move(player1);
        move(player2);
    }
}
