//
// Created by Bendi on 1/21/2018.
//

#include "GameWindow.h"
#include "GridSquare.h"
#include <iostream>
#include "Land.h"
#include "Treasure.h"
#include "Water.h"


GridSquare::GridSquare(int x,int y) : coordinates{x,y}
{
    edgeOwners[up] = nullptr;
    edgeOwners[down] = nullptr;
    edgeOwners[left] = nullptr;
    edgeOwners[right] = nullptr;
}

void GridSquare::drawGridSquare(sf::RenderTarget& target) const
{

    /*drawing the edges*/
    sf::Vertex line[2];
    line[0] = sf::Vertex(sf::Vector2f(GameWindow::MARGIN + coordinates.x*GameWindow::GRID_SIDE, GameWindow::MARGIN + coordinates.y*GameWindow::GRID_SIDE));
    line[1] = sf::Vertex(sf::Vector2f(GameWindow::MARGIN + (coordinates.x+1)*GameWindow::GRID_SIDE, GameWindow::MARGIN + (coordinates.y)*GameWindow::GRID_SIDE));

    if(edgeOwners.at(up))
    {
        line[0].color = edgeOwners.at(up)->GetColor();
        line[1].color = edgeOwners.at(up)->GetColor();
    }
    target.draw(line, 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(GameWindow::MARGIN + coordinates.x*GameWindow::GRID_SIDE+1, GameWindow::MARGIN + coordinates.y*GameWindow::GRID_SIDE));
    line[1] = sf::Vertex(sf::Vector2f(GameWindow::MARGIN + (coordinates.x)*GameWindow::GRID_SIDE+1, GameWindow::MARGIN + (coordinates.y+1)*GameWindow::GRID_SIDE));

    if(edgeOwners.at(left))
    {
        line[0].color = edgeOwners.at(left)->GetColor();
        line[1].color = edgeOwners.at(left)->GetColor();
    }
    target.draw(line, 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(GameWindow::MARGIN + (coordinates.x+1)*GameWindow::GRID_SIDE, GameWindow::MARGIN + coordinates.y*GameWindow::GRID_SIDE));
    line[1] = sf::Vertex(sf::Vector2f(GameWindow::MARGIN + (coordinates.x+1)*GameWindow::GRID_SIDE, GameWindow::MARGIN + (coordinates.y+1)*GameWindow::GRID_SIDE));

    if(edgeOwners.at(right))
    {
        line[0].color = edgeOwners.at(right)->GetColor();
        line[1].color = edgeOwners.at(right)->GetColor();
    }
    target.draw(line, 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(GameWindow::MARGIN + coordinates.x*GameWindow::GRID_SIDE, GameWindow::MARGIN + (coordinates.y+1)*GameWindow::GRID_SIDE-1));
    line[1] = sf::Vertex(sf::Vector2f(GameWindow::MARGIN + (coordinates.x+1)*GameWindow::GRID_SIDE, GameWindow::MARGIN + (coordinates.y+1)*GameWindow::GRID_SIDE-1));

    if(edgeOwners.at(down))
    {
        line[0].color = edgeOwners.at(down)->GetColor();
        line[1].color = edgeOwners.at(down)->GetColor();
    }
    target.draw(line, 2, sf::Lines);
}

void GridSquare::setEdgeOwner(Direction direction,Player* player)
{
    edgeOwners[direction] = player;
}

const Player* GridSquare::getEdgeOwner(Direction direction) const
{
    return edgeOwners.at(direction);
}

std::vector<std::vector<std::unique_ptr<GridSquare>>> GridSquare::createGridSquares(int width, int height)
{
    std::vector<std::vector<std::unique_ptr<GridSquare>>> gridSquares;
    std::vector<sf::Vector2i> lands = {{19,20},{21,20},{20,21},{20,22},{20,19},{19,19},{19,18},
                                       {5,9},{6,8},{7,8},{6,9},{7,9},{5,7},{4,10},{4,9}};
    std::vector<sf::Vector2i> treasures = {{20,20},{5,8}};

    for(int i = 0; i < height-1; i++){
        gridSquares.emplace_back(static_cast<unsigned>(width-1));
    }

    for(int i = 0; i < height-1; i++){
        for(int j = 0; j < width-1; j++)
            if (std::find(lands.begin(),lands.end(),sf::Vector2i{i,j}) != lands.end())
                gridSquares[i][j] = std::make_unique<Land>(j,i);
            else if(std::find(treasures.begin(),treasures.end(),sf::Vector2i{i,j}) != treasures.end())
                gridSquares[i][j] = std::make_unique<Treasure>(j,i);
            else
                gridSquares[i][j] = std::make_unique<Water>(j,i);
    }

    return gridSquares;
}

void GridSquare::setNeighbor(Direction direction, GridSquare* gridSquare){
    neighbors.insert(std::pair<Direction,GridSquare* const>(direction,gridSquare));
}

GridSquare* GridSquare::getNeighbor(Direction direction) const {
    return neighbors.at(direction);
}

Player* GridSquare::getOwner(std::unordered_set<const GridSquare*>& previous) const {
    Player* possibleOwner = getPossibleOwner(up);

    if(isOwnedBy(possibleOwner,previous))
        return possibleOwner;
    else
        return nullptr;
}

bool GridSquare::isOwnedBy(const Player* player, std::unordered_set<const GridSquare *>& previous) const{
    previous.insert(this);
    return isEdgeOwnedBy(up,player,previous) && isEdgeOwnedBy(down,player,previous) &&
           isEdgeOwnedBy(right,player,previous) && isEdgeOwnedBy(left,player,previous);
}

bool GridSquare::isEdgeOwnedBy(Direction direction, const Player* player, std::unordered_set<const GridSquare *>& previous) const{
    return edgeOwners.at(direction) == player ||
           (neighbors.at(direction) && (previous.find(neighbors.at(direction)) != previous.end() ||
                                        neighbors.at(direction)->isOwnedBy(player,previous)));
}

Player* GridSquare::getPossibleOwner(Direction direction) const{
    return edgeOwners.at(up) ? edgeOwners.at(up) : edgeOwners.at(down) ?
           edgeOwners.at(down) : edgeOwners.at(right) ? edgeOwners.at(right) :
           edgeOwners.at(left) ? edgeOwners.at(left) : neighbors.at(direction) ?
           neighbors.at(direction)->getPossibleOwner(direction) : nullptr;
}