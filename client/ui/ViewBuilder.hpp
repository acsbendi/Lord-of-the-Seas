//
// Created by acsbendi on 2018.10.06..
//

#ifndef LORD_OF_THE_SEAS_VIEWBUILDER_HPP
#define LORD_OF_THE_SEAS_VIEWBUILDER_HPP

#include <memory>
#include "../../common/gamecore/IMapBuilderObserver.hpp"

using std::unique_ptr;
using std::shared_ptr;

class GameWindow;
class GridSquareView;
class GridSquare;
class PlayerView;

class ViewBuilder : public IMapBuilderObserver{
public:
    explicit ViewBuilder(GameWindow& gameWindow);
    void OnShipPositionSet(Ship& ship, Position position) override;
    void OnGridSquarePositionSet(GridSquare& gridSquare, Position position) override;

private:
    unique_ptr<GridSquareView> CreateGridSquareView(GridSquare* gridSquare, Position position);

    GameWindow& gameWindow;
    shared_ptr<PlayerView> playerView;
};


#endif //LORD_OF_THE_SEAS_VIEWBUILDER_HPP
