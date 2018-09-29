#include "Map.h"
#include "IMapObserver.hpp"
#include "MapBuilder.hpp"

using std::unordered_set;
using std::remove;
using std::make_unique;


Map::Map() = default;

void Map::Notify()
{
    for(IMapObserver* observer : observers)
        observer->Update();
}

void Map::AddPoints(unordered_set<const GridSquare *> ownedSquares, Player *owner) const {
    for(auto gridSquare : ownedSquares)
        owner->AddScore(gridSquare->GetValue());
}

void Map::CheckForPoints(const GridSquare* gridSquareToCheck, unordered_set<const GridSquare*>& previouslyChecked) const {
    unordered_set<const GridSquare *> areaWithSameOwner;
    Player *owner = gridSquareToCheck->GetOwner(areaWithSameOwner);
    if (owner) {
        previouslyChecked.insert(areaWithSameOwner.begin(), areaWithSameOwner.end());
        AddPoints(areaWithSameOwner, owner);
    }
}

void Map::CountScore() const {
    unordered_set<const GridSquare*> checked;
    for(int i = 0; i < height-1; ++i)
        for(int j = 0; j < width-1; ++j){
            const GridSquare* currentGridSquare = gridSquares[i][j].get();
            if(!HasBeenChecked(currentGridSquare, checked))
                CheckForPoints(currentGridSquare, checked);
        }
}

bool Map::HasBeenChecked(const GridSquare* gridSquare, unordered_set<const GridSquare*>& previouslyChecked) const {
    return previouslyChecked.find(gridSquare) != previouslyChecked.end();
}

void Map::OnMove(){
    Notify();
}

bool Map::CheckEnd(){
    for(const auto& gridSquareList : gridSquares)
       for(const auto& gridSquare : gridSquareList)
           if(!gridSquare->CanEnd())
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