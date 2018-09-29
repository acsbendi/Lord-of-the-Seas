//
// Created by Bendi on 1/31/2018.
//

#include "Server.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::to_string;
using sf::TcpListener;
using sf::Socket;


void Server::Start() {
    PrepareForGame();

    int message;
    do{
        message = strtol(ReceiveText(*currentSocket).c_str(), nullptr,10);
        cout << message << endl;
        HandleMessage(message);
    } while(running);
}

void Server::PrepareForGame(){
    EstablishConnections();
    SendInitMessages();
    PrepareSockets();

    cout << " start " << endl;
    currentSocket = &socket1;
    running = true;
}


void Server::EstablishConnections() {
    TcpListener listener;
    listener.listen(55003);

    listener.accept(socket1);
    cout << "New client connected: " << socket1.getRemoteAddress() << endl;

    listener.accept(socket2);
    cout << "New client connected: " << socket2.getRemoteAddress() << endl;
}

void Server::SendInitMessages(){
    string message = "10";
    socket1.send(message.c_str(), message.size() + 1);
    cout << message << " sent" << endl;

    message = "20";
    socket2.send(message.c_str(), message.size() + 1);
    cout << message << " sent" << endl;

    socket1.send("s",2);
    socket2.send("s",2);
}

void Server::PrepareSockets(){
    socket1.setBlocking(false);
    socket2.setBlocking(false);
}

void Server::HandleMessage(int message) {
    switch(message){
        case 6:
            if(currentSocket == &socket1)
                currentSocket = &socket2;
            else
                currentSocket = &socket1;
            break;
        case 7:
            running = false;
            break;
        default:
            if(currentSocket == &socket1)
                SendText(to_string(message), socket2);
            else
                SendText(to_string(message), socket1);
    }
}


string Server::ReceiveText(TcpSocket &socket) {
    char buffer[1024];
    size_t received = 0;
    while(socket.receive(buffer, sizeof(buffer), received) == Socket::NotReady)
        ;
    string text{buffer};
    return text;
}

void Server::SendText(const string &message, TcpSocket &socket){
    size_t s = 0;
    while(socket.send(message.c_str(),message.size() + 1,s) == Socket::NotReady)
        cout << "t";
    cout << s << " sent: " << message << endl << endl;
}
