#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <SFML/Graphics.hpp>
#include <unordered_set>
#include <string>
#include "Ship.h"
#include "Army.h"
#include "Enums.h"
#include "Map.h"
#include "IPlayerObserver.h"
#include "IUserEventObserver.h"

using std::string;
using std::unique_ptr;
using sf::Color;

class Player : public IUserEventObserver {
public:
    Player(sf::Color color, const std::string &name);

    Ship *GetShip() const;

    sf::Color GetColor() const;

    void AddScore(int scoreToAdd);

    int GetScore() const;

    void Attach(IPlayerObserver *observer);

    void Detach(IPlayerObserver *observer);

    void OnDirectionSelected(Direction direction) override;

    void OnConfirmation(bool confirmed) override;

    void YourTurn();

protected:
    std::vector<IPlayerObserver *> observers;

    virtual void Confirmed();

    virtual void Unconfirmed();

    void LandingAccepted();

    void LandingDeclined();


private:
    static int NUMBER_OF_SHIP_MOVES;
    static int NUMBER_OF_ARMY_MOVES;


    unique_ptr<Ship> ship;
    unique_ptr<Army> army;
    const Color color;
    const string name;
    int score;
    int successfulMoves;

    enum State {
        waitingForTurn, shipMoving, armyMoving, waitingForConfirmation, armyLanding
    };
    State state;

    virtual void NotifyOnMove(Direction direction) const;

    void NotifyOnTurnEnd() const;

    void Move(Direction direction);

    void MoveShip(Direction direction);
    void MoveArmy(Direction direction);
    void LandArmy(Direction direction);
};

#endif // PLAYER_H
