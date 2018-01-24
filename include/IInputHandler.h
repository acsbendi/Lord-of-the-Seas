//
// Created by Bendi on 1/20/2018.
//

#ifndef LORD_OF_THE_SEAS_INPUTHANDLER_H
#define LORD_OF_THE_SEAS_INPUTHANDLER_H

#include "Enums.h"
#include "IInputHandlerObserver.h"

class IInputHandler {
public:
    virtual void attach(IInputHandlerObserver*) = 0;
    virtual void detach(IInputHandlerObserver*) = 0;
    virtual ~IInputHandler() = default;
};


#endif //LORD_OF_THE_SEAS_INPUTHANDLER_H
