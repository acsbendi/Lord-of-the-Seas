//
// Created by Bendi on 1/28/2018.
//

#include "Treasure.h"
#include "../utils/graphics/Graphics.h"

using std::unordered_set;

int Treasure::GetValue() const {
    return 20;
}

bool Treasure::IsSea() const {
    return false;
}

bool Treasure::IsLand() const {
    return true;
}

bool Treasure::CanEnd() const{
    unordered_set<const GridSquare*> unordered_set;
    return GetOwner(unordered_set) != nullptr;
}
