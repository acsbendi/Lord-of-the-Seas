//
// Created by Bendi on 1/31/2018.
//

#ifndef LORD_OF_THE_SEAS_ILOCALPLAYEROBSERVER_H
#define LORD_OF_THE_SEAS_ILOCALPLAYEROBSERVER_H

#include "Enums.h"
#include "IPlayerObserver.h"

class ILocalPlayerObserver{
public:
    virtual void onConfirmation(bool) = 0;
    virtual void onMove(Direction) = 0;
    virtual ~ILocalPlayerObserver() = default;
};


#endif //LORD_OF_THE_SEAS_ILOCALPLAYEROBSERVER_H