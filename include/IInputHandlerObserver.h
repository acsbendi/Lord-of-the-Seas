//
// Created by Bendi on 1/23/2018.
//

#ifndef LORD_OF_THE_SEAS_IINPUTHANDLEROBSERVER_H
#define LORD_OF_THE_SEAS_IINPUTHANDLEROBSERVER_H


class IInputHandlerObserver {
public:
    virtual void onConfirmation(bool) = 0;
    virtual void onDirectionSelected(Direction) = 0;
    virtual void onExit() = 0;
    virtual ~IInputHandlerObserver() = default;
};


#endif //LORD_OF_THE_SEAS_IINPUTHANDLEROBSERVER_H
