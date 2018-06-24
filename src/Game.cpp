#include <iostream>
#include "Game.h"

Game::Game(std::unique_ptr<Player> p1, std::unique_ptr<Player> p2) : map{}, gameEnd{false}, turnEnd{false},
                                                                     player1{std::move(p1)}, player2{std::move(p2)},
                                                                     gameWindow{Map::WIDTH, Map::HEIGHT}
{
    player1->Attach(&map);
    player2->Attach(&map);
    gameWindow.AttachWindowEventObserver(this);
    gameWindow.AttachUserEventObserver(player1.get());
    gameWindow.AttachUserEventObserver(player2.get());
    map.Attach(&gameWindow);
    currentPlayer = player1.get();
    player1->Attach(this);
    player2->Attach(this);
}

Game::Game() : Game(std::make_unique<Player>(sf::Color::Red,"Player 1"),std::make_unique<Player>(sf::Color::Magenta, "Player 2")){
}

void Game::CheckEnd()
{
    if(map.CheckEnd())
        OnExit();
}

void Game::PlayGame(int &scoreOfPlayer1, int &scoreOfPlayer2)
{
    map.InitializeGrid(player1.get(), player2.get());
    /*std::cout << "For movement, use the arrow keys." << std::endl;
    std::cout << "When a ship is next to a land square, press Enter to land your army," << std::endl;
    std::cout << "then choose the landing square by the arrow keys." << std::endl;
    std::cout << "If you choose not to disembark your army, press any key other than Enter." << std::endl;*/

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