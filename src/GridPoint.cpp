#include "GridPoint.h"
#include "Map.h"

GridPoint::GridPoint(GridSquareType gridSquareType,int x, int y) : movable{nullptr}, gridSquare{gridSquareType,x,y}
{

}

GridPoint::~GridPoint()
{
    //dtor
}

Movable* GridPoint::getMovable() const
{
    return movable;
}

void GridPoint::setMovable(Movable* m)
{
    movable = m;
}

GridPoint::GridSquare& GridPoint::getGridSquare()
{
    return gridSquare;
}

const GridPoint::GridSquare& GridPoint::getGridSquare() const
{
    return gridSquare;
}


sf::Texture GridPoint::GridSquare::waterTexture = GridSquare::createTexture("water.png");
sf::Texture GridPoint::GridSquare::landTexture = GridSquare::createTexture("land.png");
sf::Texture GridPoint::GridSquare::treasureTexture = GridSquare::createTexture("treasure.png");



GridPoint::GridSquare::GridSquare(GridSquareType type,int x, int y) : type{type}, coordinates{x,y}
{
    for(int i = 0; i < 4; ++i)
        edgeOwners.push_back(nullptr);
}

GridPoint::GridSquare::~GridSquare()
{
    //dtor
}

GridSquareType GridPoint::GridSquare::getType() const
{
    return type;
}


sf::Texture& GridPoint::GridSquare::getTexture(GridSquareType type)
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

sf::Texture GridPoint::GridSquare::createTexture(std::string name)
{
    sf::Texture texture;
    texture.loadFromFile(name);
    return texture;
}

void GridPoint::GridSquare::setEdgeOwner(Direction direction,const Player* player)
{
    edgeOwners[direction] = player;
}

void GridPoint::GridSquare::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    /*drawing the texture*/
    sf::Sprite sprite;
    sprite.setTexture(GridPoint::GridSquare::getTexture(type));
    sprite.setPosition(Map::MARGIN + coordinates.x*Map::GRID_SIDE,Map::MARGIN + coordinates.y*Map::GRID_SIDE);
    target.draw(sprite);

    /*drawing the edges*/
    sf::Vertex line[2];
    line[0] = sf::Vertex(sf::Vector2f(Map::MARGIN + coordinates.x*Map::GRID_SIDE, Map::MARGIN + coordinates.y*Map::GRID_SIDE));
    line[1] = sf::Vertex(sf::Vector2f(Map::MARGIN + (coordinates.x+1)*Map::GRID_SIDE, Map::MARGIN + (coordinates.y)*Map::GRID_SIDE));

    if(edgeOwners[up])
    {
        line[0].color = edgeOwners[up]->getColor();
        line[1].color = edgeOwners[up]->getColor();
    }
    target.draw(line, 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(Map::MARGIN + coordinates.x*Map::GRID_SIDE+1, Map::MARGIN + coordinates.y*Map::GRID_SIDE));
    line[1] = sf::Vertex(sf::Vector2f(Map::MARGIN + (coordinates.x)*Map::GRID_SIDE+1, Map::MARGIN + (coordinates.y+1)*Map::GRID_SIDE));

    if(edgeOwners[left])
    {
        line[0].color = edgeOwners[left]->getColor();
        line[1].color = edgeOwners[left]->getColor();
    }
    target.draw(line, 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(Map::MARGIN + (coordinates.x+1)*Map::GRID_SIDE, Map::MARGIN + coordinates.y*Map::GRID_SIDE));
    line[1] = sf::Vertex(sf::Vector2f(Map::MARGIN + (coordinates.x+1)*Map::GRID_SIDE, Map::MARGIN + (coordinates.y+1)*Map::GRID_SIDE));

    if(edgeOwners[right])
    {
        line[0].color = edgeOwners[right]->getColor();
        line[1].color = edgeOwners[right]->getColor();
    }
    target.draw(line, 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(Map::MARGIN + coordinates.x*Map::GRID_SIDE, Map::MARGIN + (coordinates.y+1)*Map::GRID_SIDE-1));
    line[1] = sf::Vertex(sf::Vector2f(Map::MARGIN + (coordinates.x+1)*Map::GRID_SIDE, Map::MARGIN + (coordinates.y+1)*Map::GRID_SIDE-1));

    if(edgeOwners[down])
    {
        line[0].color = edgeOwners[down]->getColor();
        line[1].color = edgeOwners[down]->getColor();
    }
    target.draw(line, 2, sf::Lines);
}

sf::Vector2i GridPoint::GridSquare::getCoordinates() const
{
    return coordinates;
}

const Player* GridPoint::GridSquare::getEdgeOwner(Direction direction) const
{
    return edgeOwners[direction];
}


