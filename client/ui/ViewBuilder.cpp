//
// Created by acsbendi on 2018.10.06..
//

#include <memory>
#include "ViewBuilder.hpp"
#include "views/ShipView.hpp"
#include "../../common/gamecore/Ship.h"

using std::unique_ptr;
using std::make_unique;
using std::move;


void ViewBuilder::OnShipPositionSet(Ship& ship, Position position) {
    unique_ptr<ShipView> newShipView = make_unique<ShipView>(position);

    ship.Attach(newShipView.get());
    gameWindow.AddMovableView(move(newShipView));
}

void ViewBuilder::OnGridSquarePositionSet(const GridSquare& square, Position position) {
}

ViewBuilder::ViewBuilder(GameWindow& gameWindow) : gameWindow{gameWindow} {

}
