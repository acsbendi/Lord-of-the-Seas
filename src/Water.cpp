//
// Created by Bendi on 1/28/2018.
//

#include "Water.h"

int Water::GetValue() const {
    return 1;
}

bool Water::IsSea() const {
    return true;
}

bool Water::IsLand() const {
    return false;
}

bool Water::CanEnd() const{
    return true;
}