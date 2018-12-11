//
// Created by acsbendi on 2018.10.06..
//

#ifndef LORD_OF_THE_SEAS_VIEWBUILDER_HPP
#define LORD_OF_THE_SEAS_VIEWBUILDER_HPP

#include <memory>
#include <unordered_map>
#include "../../common/gamecore/IMapBuilderObserver.hpp"
#include "../../common/gamecore/IPlayerObserver.h"

using std::unique_ptr;
using std::shared_ptr;
using std::unordered_map;

class GameWindow;
class GridSquareView;
class GridSquare;
class PlayerView;
class ShipView;
class ArmyView;

class ViewBuilder : public IMapBuilderObserver, public IPlayerObserver{
public:
    explicit ViewBuilder(GameWindow& gameWindow);
    void OnShipPositionSet(Ship& ship, Position position) override;
    void OnGridSquarePositionSet(GridSquare& gridSquare, Position position) override;
    void OnLanding(LandingEvent event) override;
    void OnTurnEnd() override;
    void OnMove() override;

private:
    unique_ptr<GridSquareView> CreateGridSquareView(GridSquare* gridSquare, Position position);

    GameWindow& gameWindow;
    shared_ptr<PlayerView> playerView;
    unordered_map<PlayerProxy, ShipView*> shipViews;
};


#endif //LORD_OF_THE_SEAS_VIEWBUILDER_HPP
