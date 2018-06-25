//
// Created by Bendi on 1/31/2018.
//

#include "Server.h"
#include <iostream>

Server::Server() {
    sf::TcpListener listener;
    listener.listen(55003);

    listener.accept(socket1);
    std::cout << "New client connected: " << socket1.getRemoteAddress() << std::endl;

    std::string message = "10";
    socket1.send(message.c_str(), message.size() + 1);
    std::cout << message << " sent" << std::endl;

    listener.accept(socket2);
    std::cout << "New client connected: " << socket2.getRemoteAddress() << std::endl;

    message = "20";
    socket2.send(message.c_str(), message.size() + 1);
    std::cout << message << " sent" << std::endl;

    socket1.send("s",2);
    socket2.send("s",2);

    socket1.setBlocking(false);
    socket1.setBlocking(false);
}

void Server::Start() {
    std::cout << " start " << std::endl;

    sf::TcpSocket* currentSocket = &socket1;
    int message = strtol(ReceiveText(*currentSocket).c_str(), nullptr,10);
    while(true){
        std::cout << message << std::endl;
        switch(message){
            case 6:
                if(currentSocket == &socket1)
                    currentSocket = &socket2;
                else
                    currentSocket = &socket1;
                break;
            case 7:
                return;
            default:
                if(currentSocket == &socket1)
                    SendText(std::to_string(message), socket2);
                else
                    SendText(std::to_string(message), socket1);
        }
        message = strtol(ReceiveText(*currentSocket).c_str(), nullptr,10);
    }
}


std::string Server::ReceiveText(sf::TcpSocket &socket) {
    char buffer[1024];
    std::size_t received = 0;
    while(socket.receive(buffer, sizeof(buffer), received) == sf::Socket::NotReady)
        ;
    std::string text{buffer};
    return text;
}

void Server::SendText(const std::string &message, sf::TcpSocket &socket){
    size_t s = 0;
    while(socket.send(message.c_str(),message.size() + 1,s) == sf::Socket::NotReady)
        std::cout << "t";
    std::cout << s << " sent: " << message << std::endl << std::endl;
}
