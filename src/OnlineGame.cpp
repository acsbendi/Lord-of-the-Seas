//
// Created by Bendi on 1/31/2018.
//

#include <SFML/Network.hpp>
#include <iostream>
#include "OnlineGame.h"
#include "LocalPlayer.h"
#include <thread>
#include <cstring>


OnlineGame::OnlineGame() : Game(std::make_unique<LocalPlayer>(sf::Color::Red,"Player 1"), std::make_unique<Player>(sf::Color::Magenta, "Player 2")) {
    createConnection();
    dynamic_cast<LocalPlayer*>(player1.get())->attachLocalPlayerObserver(this);
}

void OnlineGame::createConnection(){
    sf::Socket::Status status = socket.connect("localhost", 55003);
    if (status != sf::Socket::Done)
    {
        throw std::runtime_error{"Connection to the server could not be established"};
    }
}

void OnlineGame::playGame(int &scoreOfPlayer1, int &scoreOfPlayer2) {
    bool firstLocal = receiveMessages()[0] == 10;
    if(firstLocal){
        map.initializeGrid(player1.get(), player2.get());
        currentPlayer = player1.get();
    }
    else {
        map.initializeGrid(player2.get(), player1.get());
        map.setActive(false);
        currentPlayer = player2.get();
    }

    socket.setBlocking(false);

    //wait for signal to start game
    while(receiveMessages().empty())
        map.getInput();

    currentPlayer->yourTurn();

    while(!gameEnd) {
        map.getInput();
        getRemoteMove();
        if(turnEnd){
            std::cout << "player notifed" << std::endl;
            currentPlayer->yourTurn(); //the notification can only take place after the previous move was entirely completed,
            //so that the current move will only be handled by one player, who is finishing their turn
            turnEnd = false;
        }
    }

    scoreOfPlayer1 = player1->getScore();
    scoreOfPlayer2 = player2->getScore();
}

vector<int> OnlineGame::receiveMessages() {
    vector<int> res;

    char buffer[1024];
    std::size_t received = 0;
    if (socket.receive(buffer, sizeof(buffer), received) == sf::Socket::NotReady)
        return res;
    for(int i = 0; i < received;i++)
        if(buffer[i] != '\0')
            res.push_back(strtol(&buffer[i], nullptr,10));
    return res;
}

void OnlineGame::sendText(std::string message){
    socket.send(message.c_str(),message.size() + 1);
}

void OnlineGame::getRemoteMove() {
    vector<int> receivedVector = receiveMessages();
    for (int received : receivedVector)
        switch (received) {
            case 4:
                player2->onConfirmation(true);
                break;
            case 5:
                player2->onConfirmation(false);
                break;
            case -1:
                return;
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
        map.setActive(false);
        //std::thread t{[&](){this->handleRemoteInput();}};
    }
    else{
        currentPlayer = player1.get();
        map.setActive(true);
    }
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