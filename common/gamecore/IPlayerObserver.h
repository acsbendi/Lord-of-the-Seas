//
// Created by Bendi on 1/20/2018.
//

#ifndef LORD_OF_THE_SEAS_IPLAYEROBSERVER_H
#define LORD_OF_THE_SEAS_IPLAYEROBSERVER_H

#include "LandingEvent.h"


class IPlayerObserver {
public:
    virtual void OnLanding(LandingEvent event) = 0;
    virtual void OnTurnEnd() = 0;
    virtual void OnMove() = 0;
    virtual ~IPlayerObserver() = default;
};


#endif //LORD_OF_THE_SEAS_IPLAYEROBSERVER_H
