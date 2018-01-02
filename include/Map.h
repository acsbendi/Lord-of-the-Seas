#ifndef MAP_H
#define MAP_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "GridPoint.h"
#include "Player.h"
#include "Enums.h"

class Player;

class Map
{
    public:
        static int GRID_SIDE;
        static int MARGIN;

        Map();
        virtual ~Map() = default;
        GridPoint* getGridPoint(int x, int y);
        sf::RenderWindow& getWindow();
        int countGridSquares(GridSquareType,const Player* = nullptr) const;
        GridPoint* getNeighbor(const GridPoint* gridPoint, Direction direction) const;
        void setEdgeOwner(GridPoint* gridPoint1,GridPoint* gridPoint2,const Player* player);
        std::vector<GridPoint*> getEdgeNeighbors(GridPoint* gridPoint1, GridPoint* gridPoint2) const;
        void refresh();
        void initializeGrid(Player*,Player*);
        sf::Keyboard::Key getPressedKey();
        bool isLand(const GridPoint*) const;
        void countScore(Player* player1,Player* player2) const;
        bool isOwner(const GridPoint*,const Player*) const;

    protected:

    private:

    static int WIDTH;
    static int HEIGHT;

    std::vector<std::vector<std::unique_ptr<GridPoint>>> gridPoints;

    sf::RenderWindow window;

    void findIndexOf(const GridPoint*, int&, int&) const;
    bool isOwnerHelper(const GridPoint*,std::vector<const GridPoint*>&,const Player*) const;
    bool isOwnerHelper2(const GridPoint*,std::vector<const GridPoint*>&,const Player*, Direction) const;
    void addPoints(std::vector<const GridPoint*>,Player*) const;
};

#endif // MAP_H
