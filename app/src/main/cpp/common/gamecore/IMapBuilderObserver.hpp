//
// Created by acsbendi on 2018.10.06..
//

#ifndef LORD_OF_THE_SEAS_IMAPBUILDEROBSERVER_HPP
#define LORD_OF_THE_SEAS_IMAPBUILDEROBSERVER_HPP

#include "Position.hpp"

class Ship;
class GridSquare;

class IMapBuilderObserver {
public:
    virtual void OnShipPositionSet(Ship&, Position) = 0;
    virtual void OnGridSquarePositionSet(GridSquare&, Position) = 0;
    virtual ~IMapBuilderObserver() = default;
};


#endif //LORD_OF_THE_SEAS_IMAPBUILDEROBSERVER_HPP
