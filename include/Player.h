#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <SFML/Graphics.hpp>
#include <unordered_set>
#include "Ship.h"
#include "Army.h"
#include "Enums.h"
#include "Map.h"
#include "IPlayerObserver.h"
#include "IUserEventObserver.h"

class Player : public IUserEventObserver {
public:
    Player(sf::Color color, const std::string &name);

    Ship *getShip() const;

    sf::Color getColor() const;

    void addScore(int scoreToAdd);

    int getScore() const;

    void attach(IPlayerObserver * observer);

    void detach(IPlayerObserver * observer);

    void onDirectionSelected(Direction direction) override;

    void onConfirmation(bool confirmed) override;

    void yourTurn();

protected:
    std::vector<IPlayerObserver *> observers;

    virtual void confirmed();

    virtual void unconfirmed();

    void landingAccepted();

    void landingDeclined();


private:
    static int NUMBER_OF_SHIP_MOVES;
    static int NUMBER_OF_ARMY_MOVES;


    std::unique_ptr<Ship> ship;
    std::unique_ptr<Army> army;
    const sf::Color color;
    const std::string name;
    int score;
    int successfulMoves;

    enum State {
        waitingForTurn, shipMoving, armyMoving, waitingForConfirmation, armyLanding
    };
    State state;

    virtual void notifyOnMove(Direction direction) const;

    void notifyOnTurnEnd() const;

    void move(Direction direction);

    void moveShip(Direction direction);
    void moveArmy(Direction direction);
    void landArmy(Direction direction);
};

#endif // PLAYER_H
