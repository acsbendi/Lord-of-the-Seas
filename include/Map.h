#ifndef MAP_H
#define MAP_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "GridPoint.h"
#include "Player.h"
#include "GridSquare.h"
#include "Enums.h"

class Player;

class Map
{
    public:
        static int GRID_SIDE;
        static int MARGIN;

        Map();
        virtual ~Map();
        std::shared_ptr<GridPoint> getGridPoint(int x, int y);
        sf::RenderWindow& getWindow();
        int countGridSquares(GridSquareType,const std::shared_ptr<Player>& = nullptr) const;
        std::shared_ptr<GridPoint> getNeighbor(const GridPoint* gridPoint, Direction direction) const;
        void setEdgeOwner(const std::shared_ptr<GridPoint>& gridPoint1,const std::shared_ptr<GridPoint>& gridPoint2,const std::shared_ptr<Player>& player);
        void refresh();
        void initializeGrid(std::shared_ptr<Player>&, std::shared_ptr<Player>&);
        sf::Keyboard::Key getPressedKey();
        bool isLand(const std::shared_ptr<GridPoint>&) const;

    protected:

    private:

    static int WIDTH;
    static int HEIGHT;

    std::vector<std::vector<std::shared_ptr<GridPoint>>> gridPoints;

    sf::RenderWindow window;

    void findIndexOf(const GridPoint*, int&, int&) const;
};

#endif // MAP_H
