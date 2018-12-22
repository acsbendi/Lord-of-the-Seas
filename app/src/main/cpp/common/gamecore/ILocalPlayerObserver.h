//
// Created by Bendi on 1/31/2018.
//

#ifndef LORD_OF_THE_SEAS_ILOCALPLAYEROBSERVER_H
#define LORD_OF_THE_SEAS_ILOCALPLAYEROBSERVER_H

#include "../utils/Enums.h"
#include "IPlayerObserver.h"

class ILocalPlayerObserver{
public:
    virtual void OnConfirmation(bool) = 0;
    virtual void OnMove(Direction) = 0;
    virtual ~ILocalPlayerObserver() = default;
};


#endif //LORD_OF_THE_SEAS_ILOCALPLAYEROBSERVER_H
