//
// Created by Bendi on 1/26/2018.
//

#ifndef LORD_OF_THE_SEAS_IWINDOWEVENTOBSERVER_H
#define LORD_OF_THE_SEAS_IWINDOWEVENTOBSERVER_H


class IWindowEventObserver {
public:
    virtual void OnExit() = 0;
    virtual ~IWindowEventObserver() = default;
};


#endif //LORD_OF_THE_SEAS_IWINDOWEVENTOBSERVER_H
