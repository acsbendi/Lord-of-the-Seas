#include "Map.h"
#include "IMapObserver.hpp"
#include <iostream>

/*int Map::WIDTH = 40;
int Map::HEIGHT = 30;
*/

Map::Map()
{

}

void Map::InitializeGrid(Player *player1, Player *player2)
{
    gridSquares = GridSquare::createGridSquares(WIDTH, HEIGHT);

    for(int i = 0; i < HEIGHT; i++){
        gridPoints.emplace_back(static_cast<unsigned>(WIDTH));
    }

    for(int i = 0; i < HEIGHT; i++)
        for(int j = 0; j < WIDTH; j++)
                gridPoints[i][j] = std::make_unique<GridPoint>(j,i);

    SetNeighbors();

    for(int i = 0; i < HEIGHT; i++)
        for(int j = 0; j < WIDTH; j++)
            gridPoints[i][j]->finishInitialization();

    gridPoints[0][0]->setMovable(player1->GetShip());
    player1->GetShip()->SetCurrentLocation(gridPoints[0][0].get());
    gridPoints[HEIGHT-2][WIDTH-2]->setMovable(player2->GetShip());
    player2->GetShip()->SetCurrentLocation(gridPoints[HEIGHT - 2][WIDTH - 2].get());
    Notify();
}

void Map::Notify()
{
    for(IMapObserver* observer : observers)
        observer->Update(*this);
}

void Map::Show(RenderWindow& window){
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

void Map::AddPoints(std::unordered_set<const GridSquare *> ownedSquares, Player *owner) const
{
    for(auto gridSquare : ownedSquares)
        owner->AddScore(gridSquare->GetValue());
}


void Map::CountScore() const {
    std::unordered_set<const GridSquare*> checked;
    for(int i = 0; i < HEIGHT-1; ++i)
        for(int j = 0; j < WIDTH-1; ++j)
        {
            if(checked.find(gridSquares[i][j].get()) == checked.end()) {
                std::unordered_set<const GridSquare *> previous;
                Player *owner = gridSquares[i][j]->getOwner(previous);
                if (owner) {
                    checked.insert(previous.begin(), previous.end());
                    AddPoints(previous, owner);
                }
            }
        }
}

void Map::OnMove(){
    Notify();
}

void Map::SetNeighbors() {
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

bool Map::CheckEnd(){
    for(const auto& i : gridSquares)
       for(const auto& j : i)
           if(!j->CanEnd())
               return false;
    return true;
}

void Map::OnTurnEnd() {

}

void Map::Attach(IMapObserver *observer) {
    observers.push_back(observer);
}

void Map::Detach(IMapObserver *observer) {
    observers.erase(std::remove(observers.begin(),
                                observers.end(),observer),observers.end());
}