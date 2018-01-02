#include <iostream>
#include "Game.h"

int Game::NUMBER_OF_SHIP_MOVES = 3;
int Game::NUMBER_OF_ARMY_MOVES = 1;

Game::Game() : map{}, end{false}, player1{std::make_unique<Player>(sf::Color::Red)}, player2{std::make_unique<Player>(sf::Color::Magenta)}
{
    map.initializeGrid(player1.get(), player2.get());
    map.refresh();
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
            case sf::Keyboard::Escape:
                end = true;
                return left;
            default:
                continue;
        }
    }
}

void Game::checkEnd()
{
    end = end || (map.countGridSquares(GridSquareType::treasure) ==
           map.countGridSquares(GridSquareType::treasure, player1.get()) +
           map.countGridSquares(GridSquareType::treasure, player2.get()));
}

void Game::move(const std::unique_ptr<Player>& player)
{
    int countOfValidatedMoves = 0;
    while(countOfValidatedMoves < NUMBER_OF_SHIP_MOVES && !end)
    {
        Direction direction = getSelectedDirection();
        GridPoint* destination;
        try
        {
            destination = map.getNeighbor(player->getShip()->getCurrentLocation(),direction);
            if(destination->getMovable()) continue; //the destination square is occupied
            std::vector<GridPoint*> edgeNeighbors = map.getEdgeNeighbors(player->getShip()->getCurrentLocation(),destination);
            if(edgeNeighbors[0]->getGridSquare().getType() != water &&
               (!edgeNeighbors[1] || edgeNeighbors[1]->getGridSquare().getType() != water)) continue; //ships cannot move on land
            map.setEdgeOwner(player->getShip()->getCurrentLocation(),destination,player.get());
            player->getShip()->getCurrentLocation()->setMovable(nullptr);
            player->getShip()->setCurrentLocation(destination);
            destination->setMovable(player->getShip());
            if(!player->getArmy()->getCurrentLocation() && map.isLand(player->getShip()->getCurrentLocation())) landArmy(player);
            map.refresh();
            ++countOfValidatedMoves;
        }
        catch(std::out_of_range& e)
        {

        }
    }

    //army can move
    if(player->getArmy()->getCurrentLocation())
    {
        countOfValidatedMoves = 0;
        while(countOfValidatedMoves < NUMBER_OF_ARMY_MOVES && !end)
        {
            Direction direction = getSelectedDirection();
            GridPoint* destination;
            try
            {
                destination = map.getNeighbor(player->getArmy()->getCurrentLocation(),direction);
                if(destination->getMovable()) continue; //the destination square is occupied
                std::vector<GridPoint*> edgeNeighbors = map.getEdgeNeighbors(player->getArmy()->getCurrentLocation(),destination);
                if(edgeNeighbors[0]->getGridSquare().getType() == water  &&
                   (!edgeNeighbors[1] || edgeNeighbors[1]->getGridSquare().getType() == water)) continue; //armies can only move on land
                map.setEdgeOwner(player->getArmy()->getCurrentLocation(),destination,player.get());
                player->getArmy()->getCurrentLocation()->setMovable(nullptr);
                player->getArmy()->setCurrentLocation(destination);
                destination->setMovable(player->getArmy());
                map.refresh();
                ++countOfValidatedMoves;
            }
            catch(std::out_of_range& e)
            {

            }
        }
    }
}

void Game::landArmy(const std::unique_ptr<Player>& player)
{
    sf::Keyboard::Key pressedKey = map.getPressedKey();
    if(pressedKey == sf::Keyboard::Return)
    {
        player->getShip()->setArmyOnBoard(nullptr);
        while(!end)
        {
            Direction direction = getSelectedDirection();
            GridPoint* destination;
            try
            {
                destination = map.getNeighbor(player->getShip()->getCurrentLocation(),direction);
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
    std::cout << "For movement, use the arrow keys." << std::endl;
    std::cout << "When a ship is next to a land square, press Enter to land your army," << std::endl;
    std::cout << "then choose the landing square by the arrow keys." << std::endl;
    std::cout << "If you choose not to disembark your army, press any key other than Enter." << std::endl;
    while(!end)
    {
        move(player1);
        move(player2);
        checkEnd();
    }

    map.countScore(player1.get(),player2.get());
    std::cout << "First player's score: " << player1->getScore() << std::endl;
    std::cout << "Second player's score: " << player2->getScore() << std::endl;
}
