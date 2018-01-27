//
// Created by Bendi on 1/26/2018.
//

#ifndef LORD_OF_THE_SEAS_IUSEREVENTOBSERVER_H
#define LORD_OF_THE_SEAS_IUSEREVENTOBSERVER_H

#include "Enums.h"

class IUserEventObserver {
public:
    virtual void onConfirmation(bool) = 0;
    virtual void onDirectionSelected(Direction) = 0;
    virtual ~IUserEventObserver() = default;
};


#endif //LORD_OF_THE_SEAS_IUSEREVENTOBSERVER_H
