#include <iostream>
#include <functional>
#include "Player.h"

using std::make_unique;
using std::remove;

Player::Player(const string& name) :
    name{name}, state{waitingForTurn}, score{0}, successfulMoves{0}
{
    ship = make_unique<Ship>(*this);
    army = make_unique<Army>(*this);
    ship->SetArmyOnBoard(army.get());
    ship->Attach(this);
    army->Attach(this);
}

Ship* Player::GetShip() const
{
    return ship.get();
}

int Player::GetScore() const
{
    return score;
}

void Player::AddScore(int scoreToAdd){
    score += scoreToAdd;
}

void Player::Move(Direction direction)
{
    switch (state){
        case shipMoving:
            MoveShip(direction);
            break;
        case armyMoving:
            MoveArmy(direction);
            break;
        case armyLanding:
            LandArmy(direction);
            break;
        default:
            break;
    }
}

void Player::MoveShip(Direction direction){
    ship->Move(direction);
}

void Player::SetStateAfterSuccessfulMove(){
    if(ship->GetArmyOnBoard() && ship->IsAtCoast())
        state = waitingForConfirmation;
    else if(successfulMoves == NUMBER_OF_SHIP_MOVES){
        SetStateAfterLastShipMove();
    }
}

void Player::SetStateAfterLastShipMove(){
    successfulMoves = 0;
    if(army->GetCurrentLocation())
        state = armyMoving;
    else{
        state = waitingForTurn;
        NotifyOnTurnEnd();
    }
}

void Player::SetStateAfterLastArmyMove() {
    successfulMoves = 0;
    state = waitingForTurn;
    NotifyOnTurnEnd();
}

void Player::MoveArmy(Direction direction){
    army->Move(direction);
}

void Player::SuccessfulArmyMove(Direction direction){
    NotifyOnMove(direction);
    successfulMoves++;
    if(successfulMoves == NUMBER_OF_ARMY_MOVES){
        SetStateAfterLastArmyMove();
    }
}

void Player::LandArmy(Direction direction) {
    army->Move(direction);
}

void Player::LandingAccepted(){
    ship->SetArmyOnBoard(nullptr);
    army->SetCurrentLocation(ship->GetCurrentLocation());
    state = armyLanding;
}

void Player::Attach(IPlayerObserver *observer){
    observers.push_back(observer);
}

void Player::Detach(IPlayerObserver *observer){
    observers.erase(remove(observers.begin(),observers.end(),observer),observers.end());
}

void Player::NotifyOnMove(Direction) const{
    for(IPlayerObserver* observer : observers)
        observer->OnMove();
}

void Player::NotifyOnTurnEnd() const{
    for(IPlayerObserver* observer : observers)
        observer->OnTurnEnd();
}

void Player::OnDirectionSelected(Direction direction) {
    Move(direction);
}

void Player::OnConfirmation(bool confirmed) {
    if(state == waitingForConfirmation && confirmed)
        this->Confirmed();
    else if(state == waitingForConfirmation)
        Unconfirmed();
}

void Player::YourTurn() {
    state = shipMoving;
}

void Player::Unconfirmed() {
    LandingDeclined();
}

void Player::Confirmed() {
    LandingAccepted();
}

void Player::LandingDeclined() {
    if(successfulMoves == NUMBER_OF_SHIP_MOVES)
        SetStateAfterLastShipMove();
    else
        state = shipMoving;
}

void Player::NotifyOnLanding(Direction landingDirection) const {
    LandingEvent landingEvent = {
            .army = *army,
            .ship = *ship,
            .owner = CreateProxy(),
            .direction = landingDirection
    };

    for(IPlayerObserver* observer : observers)
        observer->OnLanding(landingEvent);
}

PlayerProxy Player::CreateProxy() const {
    return PlayerProxy{this};
}

void Player::OnMove(Direction moveDirection) {
    if(state == armyMoving)
        SuccessfulArmyMove(moveDirection);
    else if (state == shipMoving){
        NotifyOnMove(moveDirection);
        successfulMoves++;
        SetStateAfterSuccessfulMove();
    } else if (state == armyLanding){
        if(successfulMoves != NUMBER_OF_SHIP_MOVES)
            state = shipMoving;
        else{
            state = armyMoving;
            successfulMoves = 0;
        }

        NotifyOnLanding(moveDirection);
        NotifyOnMove(moveDirection);
    }
}