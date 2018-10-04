//
// Created by acsbendi on 2018.10.04..
//

#ifndef LORD_OF_THE_SEAS_GRIDSQUAREOBSERVER_HPP
#define LORD_OF_THE_SEAS_GRIDSQUAREOBSERVER_HPP

#include "EdgeOwnerChangedEvent.hpp"


class IGridSquareObserver {
public:
    virtual ~IGridSquareObserver() =  0;
    virtual void OnEdgeOwnerChanged(EdgeOwnerChangedEvent event) = 0;
};


#endif //LORD_OF_THE_SEAS_GRIDSQUAREOBSERVER_HPP
