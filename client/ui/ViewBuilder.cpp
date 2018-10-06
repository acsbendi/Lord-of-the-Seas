//
// Created by acsbendi on 2018.10.06..
//

#include <memory>
#include "ViewBuilder.hpp"
#include "views/ShipView.hpp"
#include "../../common/gamecore/Ship.h"
#include "views/GridSquareView.hpp"
#include "GameWindow.h"
#include "../../common/gamecore/GridSquare.h"
#include "../../common/gamecore/Land.h"
#include "views/LandView.hpp"
#include "views/TreasureView.hpp"
#include "../../common/gamecore/Treasure.h"
#include "views/WaterView.hpp"
#include "../../common/gamecore/Water.h"

using std::unique_ptr;
using std::make_unique;
using std::move;


void ViewBuilder::OnShipPositionSet(Ship& ship, Position position) {
    unique_ptr<ShipView> newShipView = make_unique<ShipView>(position);

    ship.Attach(newShipView.get());
    gameWindow.AddMovableView(move(newShipView));
}

void ViewBuilder::OnGridSquarePositionSet(GridSquare& gridSquare, Position position) {
    unique_ptr<GridSquareView> newGridSquareView = CreateGridSquareView(&gridSquare, position);

    gridSquare.Attach(newGridSquareView.get());
    gameWindow.AddGridSquareView(move(newGridSquareView));
}

ViewBuilder::ViewBuilder(GameWindow& gameWindow) : gameWindow{gameWindow} {

}

unique_ptr<GridSquareView> ViewBuilder::CreateGridSquareView(GridSquare* gridSquare, Position position) {
    if(dynamic_cast<Land*>(gridSquare)){
        return make_unique<LandView>(position);
    } else if (dynamic_cast<Water*>(gridSquare)){
        return make_unique<WaterView>(position);
    } else if (dynamic_cast<Treasure*>(gridSquare)){
        return make_unique<TreasureView>(position);
    } else{
        throw std::runtime_error{"No such type exist"};
    }
}
