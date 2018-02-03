//
// Created by Bendi on 1/31/2018.
//

#include <SFML/Network.hpp>
#include <iostream>
#include "OnlineGame.h"
#include "LocalPlayer.h"

OnlineGame::OnlineGame() : Game(std::make_unique<LocalPlayer>(sf::Color::Red,"Player 1"), std::make_unique<Player>(sf::Color::Magenta, "Player 2")) {
    createConnection();
    dynamic_cast<LocalPlayer*>(player1.get())->attachLocalPlayerObserver(this);
}

void OnlineGame::createConnection(){
    sf::Socket::Status status = socket.connect("localhost", 55001);
    if (status != sf::Socket::Done)
    {
        throw std::runtime_error{"Connection to the server could not be established"};
    }
}

void OnlineGame::playGame(int &scoreOfPlayer1, int &scoreOfPlayer2) {

    bool firstLocal = receiveText() == "first";
    if(firstLocal){
        map.initializeGrid(player1.get(), player2.get());
        currentPlayer = player1.get(); std::cout << "first";}
    else {
        map.initializeGrid(player2.get(), player1.get());
        currentPlayer = player2.get(); std::cout << " second ";}

    currentPlayer->yourTurn();

    while(!gameEnd) {
        if(player1.get() == currentPlayer)
            map.getInput();
        else
            getRemoteMove();
        if(turnEnd){
            currentPlayer->yourTurn(); //the notification can only take place after the previous move was entirely completed,
            //so that the current move will only be handled by one player, who is finishing their turn
            turnEnd = false;
        }
    }

    scoreOfPlayer1 = player1->getScore();
    scoreOfPlayer2 = player2->getScore();
}

std::string OnlineGame::receiveText() {
    char buffer[1024];
    std::size_t received = 0;
    socket.receive(buffer, sizeof(buffer), received);
    std::string text{buffer};
    std::cout << "received : " << text << std::endl;
    return text;
}

void OnlineGame::sendText(std::string message){
    socket.send(message.c_str(),message.size() + 1);
}

void OnlineGame::getRemoteMove() {
    std::cout << "getRemote" << std::endl;
    int received = strtol(receiveText().c_str(), nullptr,10);
    switch(received){
        case 4:
            player2->onConfirmation(true);
            break;
        case 5:
            player2->onConfirmation(false);
            break;
        default:
            player2->onDirectionSelected(static_cast<Direction>(received));
            break;
    }
}

void OnlineGame::onMove(Direction direction){
    sendText(std::to_string(direction));
}

void OnlineGame::onTurnEnd() {
    std::cout << "onTurnEnd" << std::endl;
    if(currentPlayer == player1.get()) {
        currentPlayer = player2.get();
        sendText(std::to_string(6));
    }
    else
        currentPlayer = player1.get();
    turnEnd = true;
}

void OnlineGame::onConfirmation(bool confirmed){
    sendText(std::to_string(confirmed ? 4 : 5));
}

void OnlineGame::onExit(){
    map.countScore();
    gameEnd = true;
    sendText(std::to_string(7));
}
