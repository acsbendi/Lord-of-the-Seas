#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <SFML/Graphics.hpp>
#include <unordered_set>
#include <string>
#include "Ship.h"
#include "Army.h"
#include "../utils/Enums.h"
#include "IPlayerObserver.h"
#include "IUserEventObserver.h"
#include "PlayerProxy.h"
#include "IMovableObserver.hpp"

using std::string;
using std::unique_ptr;
using sf::Color;
using std::vector;

class Player : public IUserEventObserver, public IMovableObserver {
public:
    Player(Color color, const string &name);
    Ship* GetShip() const;
    Color GetColor() const;
    void AddScore(int scoreToAdd);
    int GetScore() const;
    void Attach(IPlayerObserver* observer);
    void Detach(IPlayerObserver* observer);
    void OnDirectionSelected(Direction direction) override;
    void OnConfirmation(bool confirmed) override;
    void YourTurn();
    PlayerProxy CreateProxy() const;
    void OnMove(Direction moveDirection) override;

protected:
    vector<IPlayerObserver*> observers;

    virtual void Confirmed();
    virtual void Unconfirmed();
    void LandingAccepted();
    void LandingDeclined();

private:
    static constexpr int NUMBER_OF_SHIP_MOVES = 3;
    static constexpr int NUMBER_OF_ARMY_MOVES = 2;

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
    void NotifyOnLanding(Direction landingDirection) const;
    void Move(Direction direction);
    void MoveShip(Direction direction);
    void MoveArmy(Direction direction);
    void LandArmy(Direction direction);
    void SetStateAfterSuccessfulMove();
    void SetStateAfterLastShipMove();
    void SetStateAfterLastArmyMove();
    void SuccessfulArmyMove(Direction direction);
};

#endif // PLAYER_H
