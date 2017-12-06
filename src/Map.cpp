#include "Map.h"
#include <iostream>


int Map::WIDTH = 40;
int Map::HEIGHT = 30;
int Map::GRID_SIDE = 15;
int Map::MARGIN = 15;


Map::Map() : window{sf::VideoMode(Map::GRID_SIDE*(Map::WIDTH-1) + 2*MARGIN, Map::GRID_SIDE*(Map::HEIGHT-1) + 2*MARGIN),"Lord of the Seas"}
{

}

Map::~Map()
{
    //dtor
}

sf::RenderWindow& Map::getWindow()
{
    return window;
}

void Map::initializeGrid(Player* player1, Player* player2)
{
    std::vector<sf::Vector2i> lands = {{19,20},{21,20},{20,21},{20,22},{20,19},{19,19},{19,18},
                                        {5,9},{6,8},{7,8},{6,9},{7,9},{5,7},{4,10},{4,9}};
    std::vector<sf::Vector2i> treasures = {{20,20},{5,8}};

    for(int i = 0; i < HEIGHT; i++){
        gridPoints.push_back(std::vector<std::unique_ptr<GridPoint>>{(unsigned)WIDTH});
    }

    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++)
            if (std::find(lands.begin(),lands.end(),sf::Vector2i{i,j}) != lands.end())
                gridPoints[i][j] = std::unique_ptr<GridPoint>{new GridPoint{GridSquareType::land,j,i}};
            else if(std::find(treasures.begin(),treasures.end(),sf::Vector2i{i,j}) != treasures.end())
                gridPoints[i][j] = std::unique_ptr<GridPoint>{new GridPoint{GridSquareType::treasure,j,i}};
            else
                gridPoints[i][j] = std::unique_ptr<GridPoint>{new GridPoint{GridSquareType::water,j,i}};
     }

    gridPoints[0][0]->setMovable(player1->getShip());
    player1->getShip()->setCurrentLocation(gridPoints[0][0].get());
    gridPoints[HEIGHT-2][WIDTH-2]->setMovable(player2->getShip());
    player2->getShip()->setCurrentLocation(gridPoints[HEIGHT-2][WIDTH-2].get());
}

int Map::countGridSquares(GridSquareType type, const Player* player) const
{
    int result = 0;
    for(int i = 0; i < HEIGHT-1; ++i)
    {
        for(int j = 0; j < WIDTH-1; ++j)
        {
            if(type == GridSquareType::any && !player) ++result;
            else if(type == GridSquareType::any && (gridPoints[i][j])->isOwner(*this,player)) ++result;
            else if(!player && (gridPoints[i][j])->getGridSquare().getType() == type) ++result;
            else if((gridPoints[i][j])->getGridSquare().getType() == type &&
            (gridPoints[i][j])->isOwner(*this,player)) ++result;
        }
    }
    return result;
}

GridPoint* Map::getNeighbor(const GridPoint* gridPoint, Direction direction) const
{
    int x,y;
    findIndexOf(gridPoint,x,y);
    switch(direction)
    {
    case up:
        --y;
        break;
    case down:
        ++y;
        break;
    case right:
        ++x;
        break;
    case left:
        --x;
        break;
    }

    if(y < 0 || x < 0 || y >= HEIGHT || x >= WIDTH) throw std::out_of_range{"There is no neighbor in the specified direction"};
    else return gridPoints[y][x].get();
}

void Map::findIndexOf(const GridPoint* gridPoint, int& x, int& y) const
{
    for(x = 0; x < WIDTH; ++x)
        for(y = 0; y < HEIGHT; ++y)
            if(gridPoint == gridPoints[y][x].get()) return;
}

void Map::setEdgeOwner(GridPoint* gridPoint1,GridPoint* gridPoint2,const Player* player)
{
    int x1,y1,x2,y2;
    findIndexOf(gridPoint1,x1,y1);
    findIndexOf(gridPoint2,x2,y2);

    //going down
    if(y1 == y2 - 1)
    {
        gridPoint1->getGridSquare().setEdgeOwner(left, player);
        if(x1 != 0) gridPoints[y1][x1-1]->getGridSquare().setEdgeOwner(right, player);
    }

    //going up
    if(y1 == y2 + 1)
    {
        gridPoint2->getGridSquare().setEdgeOwner(left, player);
        if(x1 != 0) gridPoints[y2][x2-1]->getGridSquare().setEdgeOwner(right, player);
    }

    //going right
    if(x1 == x2 - 1)
    {
        gridPoint1->getGridSquare().setEdgeOwner(up, player);
        if(y1 != 0) gridPoints[y1-1][x1]->getGridSquare().setEdgeOwner(down, player);
    }

    //going left
    if(x1 == x2 + 1)
    {
        gridPoint2->getGridSquare().setEdgeOwner(up, player);
        if(y2 != 0) gridPoints[y2-1][x2]->getGridSquare().setEdgeOwner(down, player);
    }
}

std::vector<GridPoint*> Map::getEdgeNeighbors(GridPoint* gridPoint1, GridPoint* gridPoint2) const
{
    int x1,y1,x2,y2;
    findIndexOf(gridPoint1,x1,y1);
    findIndexOf(gridPoint2,x2,y2);
    std::vector<GridPoint*> edgeNeighbors;

    //going down
    if(y1 == y2 - 1)
    {
        edgeNeighbors.push_back(gridPoint1);
        if(x1 != 0) edgeNeighbors.push_back(gridPoints[y1][x1-1].get());
        else edgeNeighbors.push_back(nullptr);
    }

    //going up
    if(y1 == y2 + 1)
    {
        edgeNeighbors.push_back(gridPoint2);
        if(x1 != 0) edgeNeighbors.push_back(gridPoints[y2][x2-1].get());
        else edgeNeighbors.push_back(nullptr);
    }

    //going right
    if(x1 == x2 - 1)
    {
        edgeNeighbors.push_back(gridPoint1);
        if(y1 != 0) edgeNeighbors.push_back(gridPoints[y1-1][x1].get());
        else edgeNeighbors.push_back(nullptr);
    }

    //going left
    if(x1 == x2 + 1)
    {
        edgeNeighbors.push_back(gridPoint2);
        if(y2 != 0) edgeNeighbors.push_back(gridPoints[y2-1][x2].get());
        else edgeNeighbors.push_back(nullptr);
    }

    return edgeNeighbors;
}

bool Map::isLand(const GridPoint* gridPoint) const
{
    if(gridPoint->getGridSquare().getType() != water)
            return true;
    try
    {
        if(getNeighbor(gridPoint,up)->getGridSquare().getType() != water)
            return true;
    }
    catch(std::out_of_range& e)
    {

    }
    try
    {
        if(getNeighbor(gridPoint,left)->getGridSquare().getType() != water)
            return true;
    }
    catch(std::out_of_range& e)
    {

    }
    return false;
}

void Map::refresh()
{
    window.clear();
    for(int i = 0; i < HEIGHT-1; ++i)
        for(int j = 0; j < WIDTH-1; ++j)
            window.draw(gridPoints[i][j]->getGridSquare());

    for(int i = 0; i < HEIGHT; ++i)
        for(int j = 0; j < WIDTH; ++j)
            if(gridPoints[i][j]->getMovable())
                window.draw(*gridPoints[i][j]->getMovable());

    window.display();
}

sf::Keyboard::Key Map::getPressedKey()
{
    sf::Event event;
    while(true){
        while (window.pollEvent(event)){
            if(event.type == sf::Event::KeyPressed)
                return event.key.code;
            else if (event.type == sf::Event::Closed)
                window.close();
        }
    }
}
