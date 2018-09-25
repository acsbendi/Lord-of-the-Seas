//
// Created by Bendi on 1/28/2018.
//

#include "Land.h"

int Land::GetValue() const {
    return 5;
}

bool Land::IsSea() const {
    return false;
}

bool Land::IsLand() const {
    return true;
}

bool Land::CanEnd() const{
    return true;
}