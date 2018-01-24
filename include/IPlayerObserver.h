//
// Created by Bendi on 1/20/2018.
//

#ifndef LORD_OF_THE_SEAS_IPLAYEROBSERVER_H
#define LORD_OF_THE_SEAS_IPLAYEROBSERVER_H


class IPlayerObserver {
public:
    virtual void onTurnEnd() = 0;
    virtual void onMove() = 0;
    virtual ~IPlayerObserver() = default;
};


#endif //LORD_OF_THE_SEAS_IPLAYEROBSERVER_H
