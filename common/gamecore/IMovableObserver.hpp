//
// Created by Bendi on 9/9/2018.
//

#ifndef LORD_OF_THE_SEAS_IMOVABLEOBSERVER_HPP
#define LORD_OF_THE_SEAS_IMOVABLEOBSERVER_HPP

#include "../utils/Enums.h"


class IMovableObserver {
public:
    virtual void OnMove(Direction moveDirection) = 0;
    virtual ~IMovableObserver() = default;
};


#endif //LORD_OF_THE_SEAS_IMOVABLEOBSERVER_HPP
