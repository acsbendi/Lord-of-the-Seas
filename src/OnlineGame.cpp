//
// Created by Bendi on 1/31/2018.
//

#include <SFML/Network.hpp>
#include <iostream>
#include "OnlineGame.h"
#include "LocalPlayer.h"
#include <thread>
#include <cstring>

using std::cout;
using std::endl;
using std::to_string;
using std::make_unique;
using std::runtime_error;
using sf::Socket;

OnlineGame::OnlineGame() : Game(make_unique<LocalPlayer>(Color::Red,"Player 1"), make_unique<Player>(Color::Magenta, "Player 2")) {
    CreateConnection();
    dynamic_cast<LocalPlayer *>(player1.get())->AttachLocalPlayerObserver(this);
}

void OnlineGame::CreateConnection(){
    Socket::Status status = socket.connect("localhost", 55003);
    if (status != Socket::Done)
    {
        throw runtime_error{"Connection to the server could not be established"};
    }
}

void OnlineGame::PlayGame(int &scoreOfPlayer1, int &scoreOfPlayer2) {
    bool firstLocal = ReceiveMessages()[0] == 10;
    if(firstLocal){
        map.InitializeGrid(player1.get(), player2.get());
        currentPlayer = player1.get();
    }
    else {
        map.InitializeGrid(player2.get(), player1.get());
        gameWindow.SetActive(false);
        currentPlayer = player2.get();
    }

    socket.setBlocking(false);

    //wait for signal to start game
    while(ReceiveMessages().empty())
        gameWindow.GetInput();

    currentPlayer->YourTurn();

    while(!gameEnd) {
        gameWindow.GetInput();
        GetRemoteMove();
        if(turnEnd){
            cout << "player notifed" << endl;
            currentPlayer->YourTurn(); //the notification can only take place after the previous move was entirely completed,
            //so that the current move will only be handled by one player, who is finishing their turn
            turnEnd = false;
        }
    }

    scoreOfPlayer1 = player1->GetScore();
    scoreOfPlayer2 = player2->GetScore();
}

vector<int> OnlineGame::ReceiveMessages() {
    vector<int> res;

    char buffer[1024];
    size_t received = 0;
    if (socket.receive(buffer, sizeof(buffer), received) == Socket::NotReady)
        return res;
    for(int i = 0; i < received;i++)
        if(buffer[i] != '\0')
            res.push_back(strtol(&buffer[i], nullptr,10));
    return res;
}

void OnlineGame::SendText(string message){
    socket.send(message.c_str(),message.size() + 1);
}

void OnlineGame::GetRemoteMove() {
    vector<int> receivedVector = ReceiveMessages();
    for (int received : receivedVector)
        switch (received) {
            case 4:
                player2->OnConfirmation(true);
                break;
            case 5:
                player2->OnConfirmation(false);
                break;
            case -1:
                return;
            default:
                player2->OnDirectionSelected(static_cast<Direction>(received));
                break;
        }
}

void OnlineGame::OnMove(Direction direction){
    SendText(to_string(direction));
}

void OnlineGame::OnTurnEnd() {
    cout << "OnTurnEnd" << endl;
    if(currentPlayer == player1.get()) {
        currentPlayer = player2.get();
        SendText(to_string(6));
        gameWindow.SetActive(false);
        //std::thread t{[&](){this->handleRemoteInput();}};
    }
    else{
        currentPlayer = player1.get();
        gameWindow.SetActive(true);
    }
    turnEnd = true;
}

void OnlineGame::OnConfirmation(bool confirmed){
    SendText(to_string(confirmed ? 4 : 5));
}

void OnlineGame::OnExit(){
    map.CountScore();
    gameEnd = true;
    SendText(to_string(7));
}