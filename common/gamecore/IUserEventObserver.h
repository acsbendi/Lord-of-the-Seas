//
// Created by Bendi on 1/26/2018.
//

#ifndef LORD_OF_THE_SEAS_IUSEREVENTOBSERVER_H
#define LORD_OF_THE_SEAS_IUSEREVENTOBSERVER_H

#include "../utils/Enums.h"

class IUserEventObserver {
public:
    virtual void OnConfirmation(bool) = 0;
    virtual void OnDirectionSelected(Direction) = 0;
    virtual ~IUserEventObserver() = default;
};


#endif //LORD_OF_THE_SEAS_IUSEREVENTOBSERVER_H
