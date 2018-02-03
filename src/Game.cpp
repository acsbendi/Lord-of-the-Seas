#include <iostream>
#include "Game.h"

Game::Game(std::unique_ptr<Player> p1, std::unique_ptr<Player> p2) : map{}, gameEnd{false}, turnEnd{false}, player1{std::move(p1)}, player2{std::move(p2)}
{
    player1->attach(&map);
    player2->attach(&map);
    map.attachWindowEventObserver(this);
    map.attachUserEventObserver(player1.get());
    map.attachUserEventObserver(player2.get());
    currentPlayer = player1.get();
    player1->attach(this);
    player2->attach(this);
}

Game::Game() : Game(std::make_unique<Player>(sf::Color::Red,"Player 1"),std::make_unique<Player>(sf::Color::Magenta, "Player 2")){
}

void Game::checkEnd()
{
    if(map.checkEnd())
        onExit();
}

void Game::playGame(int& scoreOfPlayer1, int& scoreOfPlayer2)
{
    map.initializeGrid(player1.get(), player2.get());
    /*std::cout << "For movement, use the arrow keys." << std::endl;
    std::cout << "When a ship is next to a land square, press Enter to land your army," << std::endl;
    std::cout << "then choose the landing square by the arrow keys." << std::endl;
    std::cout << "If you choose not to disembark your army, press any key other than Enter." << std::endl;*/

    currentPlayer->yourTurn();

    while(!gameEnd) {
        map.getInput();
        if(turnEnd){
            currentPlayer->yourTurn(); //the notification can only take place after the previous move was entirely completed,
                                       //so that the current move will only be handled by one player, who is finishing their turn
            turnEnd = false;
        }
    }

   scoreOfPlayer1 = player1->getScore();
   scoreOfPlayer2 = player2->getScore();
}

void Game::onMove(){
    checkEnd();
}

void Game::onExit(){
    map.countScore();
    gameEnd = true;
}

void Game::onTurnEnd() {
    if(currentPlayer == player1.get())
        currentPlayer = player2.get();
    else
        currentPlayer = player1.get();
    turnEnd = true;
}