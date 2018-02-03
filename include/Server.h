//
// Created by Bendi on 1/31/2018.
//

#ifndef LORD_OF_THE_SEAS_SERVER_H
#define LORD_OF_THE_SEAS_SERVER_H

#include <SFML/Network.hpp>
#include <SFML/Network/TcpSocket.hpp>

class Server {
private:
    sf::TcpSocket socket1;
    sf::TcpSocket socket2;

    std::string receiveText(sf::TcpSocket& socket);
    void sendText(const std::string& message, sf::TcpSocket& socket);
public:
    Server();
    void start();
};


#endif //LORD_OF_THE_SEAS_SERVER_H
