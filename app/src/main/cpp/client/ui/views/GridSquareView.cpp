//
// Created by Bendi on 9/3/2018.
//

#include "GridSquareView.hpp"
#include "../Edge.hpp"
#include "../GameWindow.h"
#include "../../../common/gamecore/GridSquare.h"
#include "../../../common/gamecore/Player.h"
#include "PlayerView.hpp"

using std::vector;
using sf::Vertex;
using sf::Vector2f;
using sf::Vector2i;
using sf::Lines;
using sf::Sprite;

void GridSquareView::DrawGridSquare(RenderTarget& target) const
{
    Edge upperEdge = {position, {position.xCoordinate + 1, position.yCoordinate}, up};
    Edge leftEdge = {position, {position.xCoordinate, position.yCoordinate + 1}, left};
    Edge rightEdge = {{position.xCoordinate + 1, position.yCoordinate}, {position.xCoordinate + 1, position.yCoordinate + 1}, right};
    Edge bottomEdge = {{position.xCoordinate, position.yCoordinate + 1}, {position.xCoordinate + 1, position.yCoordinate + 1}, down};

    vector<const Edge*> edges = {&upperEdge, &leftEdge, &rightEdge, &bottomEdge};
    for(const Edge* edge : edges)
        DrawEdge(*edge, target);
}

void GridSquareView::DrawEdge(const Edge& edge, RenderTarget& target) const{
    Vertex line[2];
    line[0] = Vertex(Vector2f(GameWindow::MARGIN + edge.startCoordinates.xCoordinate*GameWindow::GRID_SIDE,
            GameWindow::MARGIN + edge.startCoordinates.yCoordinate*GameWindow::GRID_SIDE));
    line[1] = Vertex(Vector2f(GameWindow::MARGIN + edge.endCoordinates.xCoordinate*GameWindow::GRID_SIDE,
            GameWindow::MARGIN + edge.endCoordinates.yCoordinate*GameWindow::GRID_SIDE));

    ColorEdge(line,edge);
    target.draw(line, 2, Lines);
}

void GridSquareView::ColorEdge(Vertex* line, const Edge& edge) const{
    if(EdgeOwnerExists(edge.directionInSquare)){
        PlayerProxy edgeOwner = currentEdgeOwners.at(edge.directionInSquare);
        Color lineColor = playerView->GetColorFor(edgeOwner);

        line[0].color = lineColor;
        line[1].color = lineColor;
    }
}

void GridSquareView::draw(RenderTarget& target, RenderStates) const {
    DrawTexture(GetTexture(), target);
    DrawGridSquare(target);
}

void GridSquareView::DrawTexture(const Texture& texture, RenderTarget& target) const {
    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(GameWindow::MARGIN + position.xCoordinate*GameWindow::GRID_SIDE,
            GameWindow::MARGIN + position.yCoordinate*GameWindow::GRID_SIDE);
    target.draw(sprite);
}

GridSquareView::GridSquareView(Position position, shared_ptr<PlayerView> playerView) :
position{position}, playerView{move(playerView)} {

}

void GridSquareView::OnEdgeOwnerChanged(EdgeOwnerChangedEvent event) {
    if(EdgeOwnerExists(event.edgeDirection))
        currentEdgeOwners.find(event.edgeDirection)->second = event.newOwner;
    else
        currentEdgeOwners.emplace(event.edgeDirection, event.newOwner);
}

bool GridSquareView::EdgeOwnerExists(Direction direction) const{
    return currentEdgeOwners.find(direction) != currentEdgeOwners.end();
}