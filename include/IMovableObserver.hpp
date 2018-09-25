//
// Created by Bendi on 9/9/2018.
//

#ifndef LORD_OF_THE_SEAS_IMOVABLEOBSERVER_HPP
#define LORD_OF_THE_SEAS_IMOVABLEOBSERVER_HPP

#include "Enums.h"


class IMovableObserver {
public:
    virtual void OnSuccessfulMove(Direction directionOfMove) = 0;
    virtual ~IMovableObserver() = default;
};


#endif //LORD_OF_THE_SEAS_IMOVABLEOBSERVER_HPP
