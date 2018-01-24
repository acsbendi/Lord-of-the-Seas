#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <SFML/Graphics.hpp>
#include <unordered_set>
#include "Ship.h"
#include "Army.h"
#include "Enums.h"
#include "Map.h"
#include "IInputHandler.h"
#include "IPlayerObserver.h"

class Player : public IInputHandlerObserver
{
    public:
        explicit Player(sf::Color,IInputHandler&);
        Ship* getShip() const;
        sf::Color getColor() const;
        void addScore(int);
        int getScore() const;
        void attach(IPlayerObserver*);
        void detach(IPlayerObserver*);
        void onExit() override;
        void onDirectionSelected(Direction) override;
        void onConfirmation(bool) override;
        void yourTurn();

    protected:

    private:
        static int NUMBER_OF_SHIP_MOVES;
        static int NUMBER_OF_ARMY_MOVES;


        std::unique_ptr<Ship> ship;
        std::unique_ptr<Army> army;
        std::unordered_set<IPlayerObserver*> observers;
        const sf::Color color;
        int score;
        int successfulMoves;

        enum State { waitingForTurn, shipMoving, armyMoving, waitingForConfirmation, armyLanding};
        State state;

        void landArmy();
        void notifyOnMove() const;
        void notifyOnTurnEnd() const;
        void move(Direction);

};

#endif // PLAYER_H
