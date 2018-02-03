//
// Created by Bendi on 1/31/2018.
//

#include "Server.h"
#include <iostream>

Server::Server() {
    sf::TcpListener listener;
    listener.listen(55001);

    listener.accept(socket1);
    std::cout << "New client connected: " << socket1.getRemoteAddress() << std::endl;

    std::string message = "first";
    socket1.send(message.c_str(), message.size() + 1);
    std::cout << message << " sent" << std::endl;

    listener.accept(socket2);
    std::cout << "New client connected: " << socket2.getRemoteAddress() << std::endl;

    message = "second";
    socket2.send(message.c_str(), message.size() + 1);
    std::cout << message << " sent" << std::endl;
}

void Server::start() {
    std::cout << " start " << std::endl;

    sf::TcpSocket* currentSocket = &socket1;
    int message = strtol(receiveText(*currentSocket).c_str(), nullptr,10);
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
                    sendText(std::to_string(message),socket2);
                else
                    sendText(std::to_string(message),socket1);
        }
        message = strtol(receiveText(*currentSocket).c_str(), nullptr,10);
    }
}


std::string Server::receiveText(sf::TcpSocket& socket) {
    char buffer[1024];
    std::size_t received = 0;
    socket.receive(buffer, sizeof(buffer), received);
    std::string text{buffer};
    return text;
}

void Server::sendText(const std::string& message, sf::TcpSocket& socket){
    socket.send(message.c_str(),message.size() + 1);
}
