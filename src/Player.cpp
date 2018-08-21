#include "Player.h"
#include <iostream>

using std::make_unique;
using std::remove;

Player::Player(const Color color, const string& name) : color{color}, name{name}, state{waitingForTurn}, score{0}, successfulMoves{0}
{
    ship = make_unique<Ship>(*this);
    army = make_unique<Army>(*this);
    ship->SetArmyOnBoard(army.get());
}

Ship* Player::GetShip() const
{
    return ship.get();
}

Color Player::GetColor() const
{
    return color;
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
    if(ship->Move(direction)){
        NotifyOnMove(direction);
        successfulMoves++;
        SetStateAfterSuccessfulMove();
    }
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
    if(army->Move(direction)){
        SuccessfulArmyMove(direction);
    }
}

void Player::SuccessfulArmyMove(Direction direction){
    NotifyOnMove(direction);
    successfulMoves++;
    if(successfulMoves == NUMBER_OF_ARMY_MOVES){
        SetStateAfterLastArmyMove();
    }
}

void Player::LandArmy(Direction direction) {
    if(army->Move(direction)){
        if(successfulMoves != NUMBER_OF_SHIP_MOVES)
            state = shipMoving;
        else{
            state = armyMoving;
            successfulMoves = 0;
        }

        NotifyOnMove(direction);
    }
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