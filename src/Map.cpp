#include "Map.h"
#include "IMapObserver.hpp"
#include <MapCreator.hpp>

using std::unordered_set;
using std::remove;
using std::make_unique;


Map::Map() = default;

void Map::InitializeGrid(Player *player1, Player *player2)
{
    MapCreator mapCreator = MapCreator(WIDTH, HEIGHT);

    gridSquares = mapCreator.GetGridSquares();

    for(int i = 0; i < HEIGHT; i++){
        gridPoints.emplace_back(static_cast<unsigned>(WIDTH));
    }

    for(int i = 0; i < HEIGHT; i++)
        for(int j = 0; j < WIDTH; j++)
                gridPoints[i][j] = make_unique<GridPoint>(j,i);

    SetNeighbors();

    for(int i = 0; i < HEIGHT; i++)
        for(int j = 0; j < WIDTH; j++)
            gridPoints[i][j]->FinishInitialization();

    gridPoints[0][0]->SetMovable(player1->GetShip());
    player1->GetShip()->SetCurrentLocation(gridPoints[0][0].get());
    gridPoints[HEIGHT - 2][WIDTH - 2]->SetMovable(player2->GetShip());
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
            if(gridPoints[i][j]->GetMovable())
                window.draw(*gridPoints[i][j]->GetMovable());

    window.display();
}

void Map::AddPoints(unordered_set<const GridSquare *> ownedSquares, Player *owner) const
{
    for(auto gridSquare : ownedSquares)
        owner->AddScore(gridSquare->GetValue());
}


void Map::CountScore() const {
    unordered_set<const GridSquare*> checked;
    for(int i = 0; i < HEIGHT-1; ++i)
        for(int j = 0; j < WIDTH-1; ++j)
        {
            if(checked.find(gridSquares[i][j].get()) == checked.end()) {
                unordered_set<const GridSquare *> previous;
                Player *owner = gridSquares[i][j]->GetOwner(previous);
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
            gridPoints[i][j]->SetPointNeighbor(up, i - 1 >= 0 ? gridPoints[i - 1][j].get() : nullptr);
            gridPoints[i][j]->SetPointNeighbor(left, j - 1 >= 0 ? gridPoints[i][j - 1].get() : nullptr);
            gridPoints[i][j]->SetPointNeighbor(down, i + 1 < HEIGHT ? gridPoints[i + 1][j].get() : nullptr);
            gridPoints[i][j]->SetPointNeighbor(right, j + 1 < WIDTH ? gridPoints[i][j + 1].get() : nullptr);

            //Setting neighbors connections between squares and points
            gridPoints[i][j]->SetSquareNeighbor(northwest,
                                                i - 1 >= 0 && j - 1 >= 0 ? gridSquares[i - 1][j - 1].get() : nullptr);
            gridPoints[i][j]->SetSquareNeighbor(northeast,
                                                i - 1 >= 0 && j + 1 < WIDTH ? gridSquares[i - 1][j].get() : nullptr);
            gridPoints[i][j]->SetSquareNeighbor(southeast,
                                                i + 1 < HEIGHT && j + 1 < WIDTH ? gridSquares[i][j].get() : nullptr);
            gridPoints[i][j]->SetSquareNeighbor(southwest,
                                                i + 1 < HEIGHT && j - 1 >= 0 ? gridSquares[i][j - 1].get() : nullptr);

            //Setting neighbors connections between squares and squares
            if(i+1 < HEIGHT && j+1 < WIDTH) {
                gridSquares[i][j]->SetNeighbor(up, i - 1 >= 0 ? gridSquares[i - 1][j].get() : nullptr);
                gridSquares[i][j]->SetNeighbor(left, j - 1 >= 0 ? gridSquares[i][j - 1].get() : nullptr);
                gridSquares[i][j]->SetNeighbor(down, i + 2 < HEIGHT ? gridSquares[i + 1][j].get() : nullptr);
                gridSquares[i][j]->SetNeighbor(right, j + 2 < WIDTH ? gridSquares[i][j + 1].get() : nullptr);
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
    observers.erase(remove(observers.begin(),
                                observers.end(),observer),observers.end());
}