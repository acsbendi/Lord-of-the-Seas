#include <iostream>
#include "Game.h"
#include "../../common/gamecore/MapBuilder.hpp"
#include "../ui/ViewBuilder.hpp"

using std::move;
using std::make_unique;

Game::Game(MapBuilder&& mapInitializer) :
        player1{make_unique<Player>(Color::Red, "Player 1")}, player2{make_unique<Player>(Color::Magenta, "Player 2")},
        map{},
        gameEnd{false}, turnEnd{false},
        gameWindow{map.GetWidth(),map.GetHeight()}
{
    ViewBuilder viewBuilder{gameWindow};
    mapInitializer.Attach(&viewBuilder);
    mapInitializer.BuildMap(map, *this->player1->GetShip(), *this->player2->GetShip());
    CreateAttachments();
    currentPlayer = this->player1.get();
}

Game::Game(unique_ptr<Player>&& player1, unique_ptr<Player>&& player2, MapBuilder&& mapInitializer):
        player1{move(player1)}, player2{move(player2)},
        map{},
        gameEnd{false}, turnEnd{false},
        gameWindow{map.GetWidth(),map.GetHeight()}
{
    ViewBuilder viewBuilder{gameWindow};
    mapInitializer.Attach(&viewBuilder);
    mapInitializer.BuildMap(map);
    CreateAttachments();
}

void Game::CreateAttachments(){
    player1->Attach(&map);
    player2->Attach(&map);
    gameWindow.AttachWindowEventObserver(this);
    gameWindow.AttachUserEventObserver(player1.get());
    gameWindow.AttachUserEventObserver(player2.get());
    map.Attach(&gameWindow);
    player1->Attach(this);
    player2->Attach(this);
}

void Game::CheckEnd()
{
    if(map.CheckEnd())
        OnExit();
}

void Game::PlayGame(int &scoreOfPlayer1, int &scoreOfPlayer2)
{
    gameWindow.Show();
    currentPlayer->YourTurn();

    while(!gameEnd) {
        gameWindow.GetInput();
        if(turnEnd){
            currentPlayer->YourTurn(); //the notification can only take place after the previous move was entirely completed,
                                       //so that the current move will only be handled by one player, who is finishing their turn
            turnEnd = false;
        }
    }

   scoreOfPlayer1 = player1->GetScore();
   scoreOfPlayer2 = player2->GetScore();
}

void Game::OnMove(){
    CheckEnd();
}

void Game::OnExit(){
    map.CountScore();
    gameEnd = true;
}

void Game::OnTurnEnd() {
    if(currentPlayer == player1.get())
        currentPlayer = player2.get();
    else
        currentPlayer = player1.get();
    turnEnd = true;
}

void Game::OnLanding(LandingEvent) {
    CheckEnd();
}
