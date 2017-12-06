#include "Game.h"

int Game::NUMBER_OF_MOVES = 3;

Game::Game() : map{}
{
    player1 = std::unique_ptr<Player> {new Player{sf::Color::Red}};
    player2 = std::unique_ptr<Player> {new Player{sf::Color::Magenta}};
    map.initializeGrid(player1.get(), player2.get());
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
           map.countGridSquares(GridSquareType::treasure, player1.get()) +
           map.countGridSquares(GridSquareType::treasure, player2.get());
}

void Game::move(const std::unique_ptr<Player>& player)
{
    int countOfValidatedMoves = 0;
    while(countOfValidatedMoves < NUMBER_OF_MOVES)
    {
        Direction direction = getSelectedDirection();
        GridPoint* destination;
        try
        {
            destination = map.getNeighbor(player->getShip()->getCurrentLocation(),direction);
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
        while(countOfValidatedMoves < NUMBER_OF_MOVES)
        {
            Direction direction = getSelectedDirection();
            GridPoint* destination;
            try
            {
                destination = map.getNeighbor(player->getArmy()->getCurrentLocation(),direction);
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
        while(true)
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
    while(!hasEnded())
    {
        move(player1);
        move(player2);
    }
}
