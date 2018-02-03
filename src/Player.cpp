#include "Player.h"
#include <iostream>

int Player::NUMBER_OF_SHIP_MOVES = 3;
int Player::NUMBER_OF_ARMY_MOVES = 2;

Player::Player(const sf::Color color, const std::string& name) : color{color}, name{name}, state{waitingForTurn}, score{0}, successfulMoves{0}
{
    ship = std::make_unique<Ship>(*this);
    army = std::make_unique<Army>(*this);
    ship->setArmyOnBoard(army.get());
}

Ship* Player::getShip() const
{
    return ship.get();
}

sf::Color Player::getColor() const
{
    return color;
}

int Player::getScore() const
{
    return score;
}

void Player::addScore(int scoreToAdd){
    score += scoreToAdd;
}

void Player::move(Direction direction)
{
    std::cout << "move " << state << " " << successfulMoves <<std::endl;
    switch (state){
        case shipMoving:
            moveShip(direction);
            break;
        case armyMoving:
            moveArmy(direction);
            break;
        case armyLanding:
            landArmy(direction);
            break;
        default:
            break;
    }
}

void Player::moveShip(Direction direction){
    if(ship->move(direction)){
        notifyOnMove(direction);
        successfulMoves++;
        if(ship->getArmyOnBoard() && ship->isAtCoast())
            state = waitingForConfirmation;
        else if(successfulMoves == NUMBER_OF_SHIP_MOVES){
            successfulMoves = 0;
            if(army->getCurrentLocation())
                state = armyMoving;
            else{
                state = waitingForTurn;
                notifyOnTurnEnd();
            }
        }
    }
}

void Player::moveArmy(Direction direction){
    if(army->move(direction)){
        notifyOnMove(direction);
        successfulMoves++;
        if(successfulMoves == NUMBER_OF_ARMY_MOVES){
            successfulMoves = 0;
            state = waitingForTurn;
            notifyOnTurnEnd();
        }
    }
}

void Player::landArmy(Direction direction) {
    if(army->move(direction)){
        if(successfulMoves != NUMBER_OF_SHIP_MOVES)
            state = shipMoving;
        else{
            state = armyMoving;
            successfulMoves = 0;
        }

        notifyOnMove(direction);
    }
}

void Player::landingAccepted(){
    ship->setArmyOnBoard(nullptr);
    army->setCurrentLocation(ship->getCurrentLocation());
    state = armyLanding;
}

void Player::attach(IPlayerObserver* observer){
    observers.push_back(observer);
}

void Player::detach(IPlayerObserver* observer){
    observers.erase(std::remove(observers.begin(),observers.end(),observer),observers.end());
}

void Player::notifyOnMove(Direction direction) const{
    for(IPlayerObserver* observer : observers)
        observer->onMove();
}

void Player::notifyOnTurnEnd() const{
    for(IPlayerObserver* observer : observers)
        observer->onTurnEnd();
}

void Player::onDirectionSelected(Direction direction) {
    move(direction);
}

void Player::onConfirmation(bool confirmed) {
    if(state == waitingForConfirmation && confirmed)
        this->confirmed();
    else if(state == waitingForConfirmation){
        unconfirmed();
    }
}

void Player::yourTurn() {
    state = shipMoving;
}

void Player::unconfirmed() {
    landingDeclined();
}

void Player::confirmed() {
    landingAccepted();
}

void Player::landingDeclined() {
    if(successfulMoves == NUMBER_OF_SHIP_MOVES){
        successfulMoves = 0;
        if(army->getCurrentLocation())
            state = armyMoving;
        else{
            state = waitingForTurn;
            notifyOnTurnEnd();
        }
    }
    else
        state = shipMoving;
}