//
// Created by Bendi on 1/21/2018.
//

#include "GridSquare.h"
#include <iostream>

sf::Texture GridSquare::waterTexture = GridSquare::createTexture("water.png");
sf::Texture GridSquare::landTexture = GridSquare::createTexture("land.png");
sf::Texture GridSquare::treasureTexture = GridSquare::createTexture("treasure.png");

sf::Texture& GridSquare::getTexture(Type type)
{
    switch(type)
    {
        case water:
            return GridSquare::waterTexture;
        case land:
            return GridSquare::landTexture;
        case treasure:
            return GridSquare::treasureTexture;
        default:
            return GridSquare::waterTexture;
    }
}

sf::Texture GridSquare::createTexture(std::string name)
{
    sf::Texture texture;
    texture.loadFromFile(name);
    return texture;
}

GridSquare::GridSquare(Type type,int x,int y) : type{type}, coordinates{x,y}
{
    edgeOwners[up] = nullptr;
    edgeOwners[down] = nullptr;
    edgeOwners[left] = nullptr;
    edgeOwners[right] = nullptr;
}

void GridSquare::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    /*drawing the texture*/
    sf::Sprite sprite;
    sprite.setTexture(GridSquare::getTexture(type));
    sprite.setPosition(Map::MARGIN + coordinates.x*Map::GRID_SIDE,Map::MARGIN + coordinates.y*Map::GRID_SIDE);
    target.draw(sprite);

    /*drawing the edges*/
    sf::Vertex line[2];
    line[0] = sf::Vertex(sf::Vector2f(Map::MARGIN + coordinates.x*Map::GRID_SIDE, Map::MARGIN + coordinates.y*Map::GRID_SIDE));
    line[1] = sf::Vertex(sf::Vector2f(Map::MARGIN + (coordinates.x+1)*Map::GRID_SIDE, Map::MARGIN + (coordinates.y)*Map::GRID_SIDE));

    if(edgeOwners.at(up))
    {
        line[0].color = edgeOwners.at(up)->getColor();
        line[1].color = edgeOwners.at(up)->getColor();
    }
    target.draw(line, 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(Map::MARGIN + coordinates.x*Map::GRID_SIDE+1, Map::MARGIN + coordinates.y*Map::GRID_SIDE));
    line[1] = sf::Vertex(sf::Vector2f(Map::MARGIN + (coordinates.x)*Map::GRID_SIDE+1, Map::MARGIN + (coordinates.y+1)*Map::GRID_SIDE));

    if(edgeOwners.at(left))
    {
        line[0].color = edgeOwners.at(left)->getColor();
        line[1].color = edgeOwners.at(left)->getColor();
    }
    target.draw(line, 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(Map::MARGIN + (coordinates.x+1)*Map::GRID_SIDE, Map::MARGIN + coordinates.y*Map::GRID_SIDE));
    line[1] = sf::Vertex(sf::Vector2f(Map::MARGIN + (coordinates.x+1)*Map::GRID_SIDE, Map::MARGIN + (coordinates.y+1)*Map::GRID_SIDE));

    if(edgeOwners.at(right))
    {
        line[0].color = edgeOwners.at(right)->getColor();
        line[1].color = edgeOwners.at(right)->getColor();
    }
    target.draw(line, 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(Map::MARGIN + coordinates.x*Map::GRID_SIDE, Map::MARGIN + (coordinates.y+1)*Map::GRID_SIDE-1));
    line[1] = sf::Vertex(sf::Vector2f(Map::MARGIN + (coordinates.x+1)*Map::GRID_SIDE, Map::MARGIN + (coordinates.y+1)*Map::GRID_SIDE-1));

    if(edgeOwners.at(down))
    {
        line[0].color = edgeOwners.at(down)->getColor();
        line[1].color = edgeOwners.at(down)->getColor();
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
                gridSquares[i][j] = std::make_unique<GridSquare>(land,j,i);
            else if(std::find(treasures.begin(),treasures.end(),sf::Vector2i{i,j}) != treasures.end())
                gridSquares[i][j] = std::make_unique<GridSquare>(treasure,j,i);
            else
                gridSquares[i][j] = std::make_unique<GridSquare>(water,j,i);
    }


    return gridSquares;
}

int GridSquare::getValue() const {
    switch(type)
    {
        case water:
            return 1;
        case land:
            return 5;
        case treasure:
           return 20;
        default:
            return 0;
    }
}

void GridSquare::setNeighbor(Direction direction, GridSquare* gridSquare){
    neighbors.insert(std::pair<Direction,GridSquare* const>(direction,gridSquare));
}

GridSquare* GridSquare::getNeighbor(Direction direction) const {
    return neighbors.at(direction);
}

bool GridSquare::isSea() const {
    return type == water;
}

bool GridSquare::isLand() const {
    return type != water;
}

Player* GridSquare::getOwner(std::unordered_set<const GridSquare*>& previous) const {
    Player* possibleOwner = getPossibleOwner(up);

    if(isOwnedBy(possibleOwner,previous))
        return possibleOwner;
    else
        return nullptr;

    /*addPossibleOwners(up,previous,possibleOwners);
    addPossibleOwners(down,previous,possibleOwners);
    addPossibleOwners(left,previous,possibleOwners);
    addPossibleOwners(right,previous,possibleOwners);

    if(possibleOwners.empty())
        return nullptr;
    else if(possibleOwners.size() == 1)
        return *possibleOwners.begin();
    else{
        for(auto i = possibleOwners.begin(); i != possibleOwners.end(); ++i)
            if(*i != *possibleOwners.begin()) return nullptr;
        return *possibleOwners.begin();*/
}

/*void GridSquare::addPossibleOwners(Direction direction, std::unordered_set<const GridSquare *>& previous, std::unordered_set<const Player*> possibleOwners) const{
    if(edgeOwners.at(direction))
        possibleOwners.insert(edgeOwners.at(up));
    else if(neighbors.at(direction) && previous.find(neighbors.at(direction)) == previous.end() && neighbors.at(direction)->getOwner(previous))
        possibleOwners.insert(neighbors.at(direction)->getOwner(previous));
}*/

bool GridSquare::canEnd() const {
    std::unordered_set<const GridSquare*> unordered_set;
    switch (type){
        case treasure:
            return getOwner(unordered_set) != nullptr;
        default:
            return true;
    }
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