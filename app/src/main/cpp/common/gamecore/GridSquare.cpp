//
// Created by Bendi on 1/21/2018.
//

#include <iostream>
#include <algorithm>
#include "GridSquare.h"
#include "Player.h"
#include "EdgeOwnerChangedEvent.hpp"
#include "IGridSquareObserver.hpp"

using std::pair;
using std::find;
using std::make_unique;

GridSquare::GridSquare()
{
    edgeOwners[up] = nullptr;
    edgeOwners[down] = nullptr;
    edgeOwners[left] = nullptr;
    edgeOwners[right] = nullptr;
}

void GridSquare::SetEdgeOwner(Direction direction, Player* player)
{
    edgeOwners[direction] = player;
    NotifyOnEdgeOwnerChanged(direction, player);
}

void GridSquare::SetNeighbor(Direction direction, GridSquare* gridSquare){
    neighbors.insert(pair<Direction,GridSquare* const>(direction,gridSquare));
}

Player* GridSquare::GetOwner(unordered_set<const GridSquare*>& previous) const {
    Player* possibleOwner = GetPossibleOwner(up);

    if(IsOwnedBy(possibleOwner, previous))
        return possibleOwner;
    else
        return nullptr;
}

bool GridSquare::IsOwnedBy(const Player* player, unordered_set<const GridSquare*>& previous) const{
    previous.insert(this);
    return IsEdgeOwnedBy(up, player, previous) && IsEdgeOwnedBy(down, player, previous) &&
            IsEdgeOwnedBy(right, player, previous) && IsEdgeOwnedBy(left, player, previous);
}

bool GridSquare::IsEdgeOwnedBy(Direction direction, const Player* player,
                               unordered_set<const GridSquare*>& previous) const{
    return edgeOwners.at(direction) == player ||
           (neighbors.at(direction) && (previous.find(neighbors.at(direction)) != previous.end() ||
                   neighbors.at(direction)->IsOwnedBy(player, previous)));
}

Player* GridSquare::GetPossibleOwner(Direction direction) const{
    return edgeOwners.at(up) ? edgeOwners.at(up) :
           edgeOwners.at(down) ? edgeOwners.at(down) :
           edgeOwners.at(right) ? edgeOwners.at(right) :
           edgeOwners.at(left) ? edgeOwners.at(left) :
           neighbors.at(direction) ? neighbors.at(direction)->GetPossibleOwner(direction) :
           nullptr;
}

void GridSquare::Attach(IGridSquareObserver* observer) {
    observers.push_back(observer);
}

void GridSquare::NotifyOnEdgeOwnerChanged(Direction edgeDirection, Player* newOwner){
    EdgeOwnerChangedEvent event = {
            .previousOwner = edgeOwners[edgeDirection]->CreateProxy(),
            .newOwner = newOwner->CreateProxy(),
            .edgeDirection = edgeDirection
    };

    for(IGridSquareObserver* observer : observers)
        observer->OnEdgeOwnerChanged(event);
}