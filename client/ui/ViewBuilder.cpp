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

using std::unique_ptr;
using std::make_unique;
using std::move;


void ViewBuilder::OnShipPositionSet(Ship& ship, Position position) {
    unique_ptr<ShipView> newShipView = make_unique<ShipView>(position);

    ship.Attach(newShipView.get());
    gameWindow.AddMovableView(move(newShipView));
}

void ViewBuilder::OnGridSquarePositionSet(GridSquare& square, Position position) {
    unique_ptr<GridSquareView> newGridSquareView = make_unique<GridSquareView>(position);

    square.Attach(newGridSquareView.get());
    gameWindow.AddGridSquareView(move(newGridSquareView));
}

ViewBuilder::ViewBuilder(GameWindow& gameWindow) : gameWindow{gameWindow} {

}
