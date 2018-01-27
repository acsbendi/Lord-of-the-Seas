#include "Map.h"
#include <iostream>


int Map::WIDTH = 40;
int Map::HEIGHT = 30;
int Map::GRID_SIDE = 15;
int Map::MARGIN = 15;


Map::Map() : window{sf::VideoMode(static_cast<unsigned>(Map::GRID_SIDE*(Map::WIDTH-1) + 2*MARGIN),
                                  static_cast<unsigned>(Map::GRID_SIDE*(Map::HEIGHT-1) + 2*MARGIN)),"Lord of the Seas"}
{

}

void Map::initializeGrid(Player* player1, Player* player2)
{
    gridSquares = GridSquare::createGridSquares(WIDTH, HEIGHT);

    for(int i = 0; i < HEIGHT; i++){
        gridPoints.emplace_back(static_cast<unsigned>(WIDTH));
    }

    for(int i = 0; i < HEIGHT; i++)
        for(int j = 0; j < WIDTH; j++)
                gridPoints[i][j] = std::make_unique<GridPoint>(j,i);

    setNeighbors();

    for(int i = 0; i < HEIGHT; i++)
        for(int j = 0; j < WIDTH; j++)
            gridPoints[i][j]->finishInitialization();

    gridPoints[0][0]->setMovable(player1->getShip());
    player1->getShip()->setCurrentLocation(gridPoints[0][0].get());
    gridPoints[HEIGHT-2][WIDTH-2]->setMovable(player2->getShip());
    player2->getShip()->setCurrentLocation(gridPoints[HEIGHT-2][WIDTH-2].get());
    refresh();
}

void Map::refresh()
{
    window.clear();
    for(int i = 0; i < HEIGHT-1; ++i)
        for(int j = 0; j < WIDTH-1; ++j)
            window.draw(*gridSquares[i][j]);

    for(int i = 0; i < HEIGHT; ++i)
        for(int j = 0; j < WIDTH; ++j)
            if(gridPoints[i][j]->getMovable())
                window.draw(*gridPoints[i][j]->getMovable());

    window.display();
}

void Map::addPoints(std::unordered_set<const GridSquare*> ownedSquares, Player* owner) const
{
    for(auto gridSquare : ownedSquares)
        owner->addScore(gridSquare->getValue());
}


void Map::countScore() const
{
    std::unordered_set<const GridSquare*> checked;
    for(int i = 0; i < HEIGHT-1; ++i)
        for(int j = 0; j < WIDTH-1; ++j)
        {
            if(checked.find(gridSquares[i][j].get()) == checked.end()) {
                std::unordered_set<const GridSquare *> previous;
                Player *owner = gridSquares[i][j]->getOwner(previous);
                if (owner) {
                    checked.insert(previous.begin(), previous.end());
                    addPoints(previous, owner);
                }
            }
        }
}

void Map::onMove(){
    refresh();
}

void Map::setNeighbors() {
    for(int i = 0; i < HEIGHT; ++i)
        for(int j = 0; j < WIDTH; ++j){
            //Setting neighbors connections between points and points
            gridPoints[i][j]->setPointNeighbor(up,i-1 >= 0 ? gridPoints[i-1][j].get() : nullptr);
            gridPoints[i][j]->setPointNeighbor(left, j-1 >= 0 ? gridPoints[i][j-1].get() : nullptr);
            gridPoints[i][j]->setPointNeighbor(down, i+1 < HEIGHT ? gridPoints[i+1][j].get() : nullptr);
            gridPoints[i][j]->setPointNeighbor(right, j+1 < WIDTH ? gridPoints[i][j+1].get() : nullptr);

            //Setting neighbors connections between squares and points
            gridPoints[i][j]->setSquareNeighbor(northwest, i-1 >= 0 && j-1 >= 0 ? gridSquares[i-1][j-1].get() : nullptr);
            gridPoints[i][j]->setSquareNeighbor(northeast, i-1 >= 0 && j+1 < WIDTH ? gridSquares[i-1][j].get() : nullptr);
            gridPoints[i][j]->setSquareNeighbor(southeast, i+1 < HEIGHT && j+1 < WIDTH ? gridSquares[i][j].get() : nullptr);
            gridPoints[i][j]->setSquareNeighbor(southwest, i+1 < HEIGHT && j-1 >= 0 ? gridSquares[i][j-1].get() : nullptr);

            //Setting neighbors connections between squares and squares
            if(i+1 < HEIGHT && j+1 < WIDTH) {
                gridSquares[i][j]->setNeighbor(up, i - 1 >= 0 ? gridSquares[i - 1][j].get() : nullptr);
                gridSquares[i][j]->setNeighbor(left, j - 1 >= 0 ? gridSquares[i][j - 1].get() : nullptr);
                gridSquares[i][j]->setNeighbor(down, i + 2 < HEIGHT ? gridSquares[i + 1][j].get() : nullptr);
                gridSquares[i][j]->setNeighbor(right, j + 2 < WIDTH ? gridSquares[i][j + 1].get() : nullptr);
            }
        }
}

bool Map::checkEnd(){
    for(const auto& i : gridSquares)
       for(const auto& j : i)
           if(!j->canEnd())
               return false;
    return true;
}

void Map::attachUserEventObserver(IUserEventObserver * observer){
    userEventObservers.push_back(observer);
}

void Map::detachUserEventObserver(IUserEventObserver * observer){
    userEventObservers.erase(std::remove(userEventObservers.begin(),
                                         userEventObservers.end(),observer),userEventObservers.end());
}

void Map::attachWindowEventObserver(IWindowEventObserver * observer){
    windowEventObservers.push_back(observer);
}

void Map::detachWindowEventObserver(IWindowEventObserver * observer){
    windowEventObservers.erase(std::remove(windowEventObservers.begin(),
                                           windowEventObservers.end(),observer),windowEventObservers.end());
}

void Map::notifyOnExit() const {
    for(auto observer : windowEventObservers)
        observer->onExit();
}

void Map::notifyOnConfirmation(bool confirmed) const {
    for(auto observer : userEventObservers)
        observer->onConfirmation(confirmed);
}

void Map::notifyOnDirectionSelected(Direction direction) const {
    for(auto observer : userEventObservers)
        observer->onDirectionSelected(direction);
}

void Map::getInput(){
    sf::Event event;
    while(true){
        while (window.pollEvent(event)){
            if(event.type == sf::Event::KeyPressed)
                switch(event.key.code) {
                    case sf::Keyboard::Up:
                        notifyOnDirectionSelected(up);
                        return;
                    case sf::Keyboard::Down:
                        notifyOnDirectionSelected(down);
                        return;
                    case sf::Keyboard::Right:
                        notifyOnDirectionSelected(right);
                        return;
                    case sf::Keyboard::Left:
                        notifyOnDirectionSelected(left);
                        return;
                    case sf::Keyboard::Escape:
                        notifyOnExit();
                        return;
                    case sf::Keyboard::Return:
                        notifyOnConfirmation(true);
                        return;
                    default:
                        notifyOnConfirmation(false);
                        return;
                }
            else if (event.type == sf::Event::Closed) {
                notifyOnExit();
                window.close();
                return;
            }
        }
    }
}

void Map::onTurnEnd() {

}