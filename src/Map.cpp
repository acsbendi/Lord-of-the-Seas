#include "Map.h"
#include "IMapObserver.hpp"
#include <MapBuilder.hpp>

using std::unordered_set;
using std::remove;
using std::make_unique;


Map::Map() = default;

void Map::Notify()
{
    for(IMapObserver* observer : observers)
        observer->Update(*this);
}

void Map::Show(RenderWindow& window){
    window.clear();
    for(int i = 0; i < height-1; ++i)
        for(int j = 0; j < width-1; ++j)
            window.draw(*gridSquares[i][j]);

    for(int i = 0; i < height; ++i)
        for(int j = 0; j < width; ++j)
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
    for(int i = 0; i < height-1; ++i)
        for(int j = 0; j < width-1; ++j)
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

int Map::GetHeight() const {
    return height;
}

int Map::GetWidth() const {
    return width;
}