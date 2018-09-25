//
// Created by Bendi on 9/3/2018.
//

#include "GridSquareView.hpp"
#include "Edge.hpp"
#include "GameWindow.h"
#include "GridSquare.h"
#include "Player.h"

using std::vector;
using sf::Vertex;
using sf::Vector2f;
using sf::Vector2i;
using sf::Lines;
using sf::Sprite;

void GridSquareView::DrawGridSquare(RenderTarget& target) const
{
    Edge upperEdge = {coordinates, {coordinates.x + 1, coordinates.y}, up};
    Edge leftEdge = {coordinates, {coordinates.x, coordinates.y + 1}, left};
    Edge rightEdge = {{coordinates.x + 1, coordinates.y}, {coordinates.x + 1, coordinates.y + 1}, right};
    Edge bottomEdge = {{coordinates.x, coordinates.y + 1}, {coordinates.x + 1, coordinates.y + 1}, down};

    vector<const Edge*> edges = {&upperEdge, &leftEdge, &rightEdge, &bottomEdge};
    for(const Edge* edge : edges)
        DrawEdge(*edge, target);
}

void GridSquareView::DrawEdge(const Edge& edge, RenderTarget& target) const{
    Vertex line[2];
    line[0] = Vertex(Vector2f(GameWindow::MARGIN + edge.startCoordinates.x*GameWindow::GRID_SIDE, GameWindow::MARGIN + edge.startCoordinates.y*GameWindow::GRID_SIDE));
    line[1] = Vertex(Vector2f(GameWindow::MARGIN + edge.endCoordinates.x*GameWindow::GRID_SIDE, GameWindow::MARGIN + edge.endCoordinates.y*GameWindow::GRID_SIDE));

    ColorEdge(line,edge);
    target.draw(line, 2, Lines);
}

void GridSquareView::ColorEdge(Vertex* line, const Edge& edge) const{
    if(gridSquare.edgeOwners.at(edge.directionInSquare))
    {
        line[0].color = gridSquare.edgeOwners.at(edge.directionInSquare)->GetColor();
        line[1].color = gridSquare.edgeOwners.at(edge.directionInSquare)->GetColor();
    }
}

void GridSquareView::draw(RenderTarget& target, RenderStates) const {
    DrawTexture(GetTexture(), target);
    DrawGridSquare(target);
}

void GridSquareView::DrawTexture(const Texture& texture, RenderTarget& target) const {
    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(GameWindow::MARGIN + coordinates.x*GameWindow::GRID_SIDE,GameWindow::MARGIN + coordinates.y*GameWindow::GRID_SIDE);
    target.draw(sprite);
}

GridSquareView::GridSquareView(int x,int y, const GridSquare& gridSqure) : coordinates{x,y}, gridSquare{gridSquare} {

}