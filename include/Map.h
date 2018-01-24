#ifndef MAP_H
#define MAP_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "GridPoint.h"
#include "GridSquare.h"
#include "Player.h"
#include "Enums.h"
#include "IInputHandler.h"
#include "IPlayerObserver.h"
#include "IInputHandlerObserver.h"

class GridSquare;

class Map : public IInputHandler, public IPlayerObserver
{
    public:
        static int GRID_SIDE;
        static int MARGIN;

        Map();
        //int countGridSquares(Type,const Player* = nullptr) const;
        void initializeGrid(Player*,Player*);
        void setNeighbors();
        void countScore() const;
        /*bool isOwner(const GridPoint*,const Player*) const;*/
        void onMove() override;
        void attach(IInputHandlerObserver*) override;
        void detach(IInputHandlerObserver*) override;
        bool checkEnd();
        void getInput();
        void onTurnEnd() override;

    protected:

    private:

    static int WIDTH;
    static int HEIGHT;

    std::vector<std::vector<std::unique_ptr<GridPoint>>> gridPoints;
    std::vector<std::vector<std::unique_ptr<GridSquare>>> gridSquares;
    std::unordered_set<IInputHandlerObserver*> observers;

    sf::RenderWindow window;

    /*void findIndexOf(const GridPoint*, int&, int&) const;
    bool isOwnerHelper(const GridPoint*,std::vector<const GridPoint*>&,const Player*) const;
    bool isOwnerHelper2(const GridPoint*,std::vector<const GridPoint*>&,const Player*, Direction) const;*/
    void addPoints(std::unordered_set<const GridSquare*> ownedSquares, Player* owner) const;
    void refresh();
    void notifyOnExit() const;
    void notifyOnDirectionSelected(Direction) const;
    void notifyOnConfirmation(bool) const;
};

#endif // MAP_H
