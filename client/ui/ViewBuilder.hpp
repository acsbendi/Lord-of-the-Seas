//
// Created by acsbendi on 2018.10.06..
//

#ifndef LORD_OF_THE_SEAS_VIEWBUILDER_HPP
#define LORD_OF_THE_SEAS_VIEWBUILDER_HPP


#include "../../common/gamecore/IMapBuilderObserver.hpp"

class GameWindow;

class ViewBuilder : public IMapBuilderObserver{
public:
    explicit ViewBuilder(GameWindow& gameWindow);
    void OnShipPositionSet(Ship& ship, Position position) override;
    void OnGridSquarePositionSet(GridSquare& square, Position position) override;

private:

    GameWindow& gameWindow;
};


#endif //LORD_OF_THE_SEAS_VIEWBUILDER_HPP
