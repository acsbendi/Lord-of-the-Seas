//
// Created by Bendi on 1/31/2018.
//

#ifndef LORD_OF_THE_SEAS_SERVER_H
#define LORD_OF_THE_SEAS_SERVER_H

#include <string>
#include <SFML/Network.hpp>
#include <SFML/Network/TcpSocket.hpp>

using sf::TcpSocket;
using std::string;

class Server {
private:
    TcpSocket socket1;
    TcpSocket socket2;
    TcpSocket* currentSocket;
    bool running;

    string ReceiveText(TcpSocket& socket);
    void SendText(const string& message, TcpSocket& socket);
    void HandleMessage(int message);
    void PrepareForGame();
    void EstablishConnections();
    void SendInitMessages();
    void PrepareSockets();

public:
    void Start();
};


#endif //LORD_OF_THE_SEAS_SERVER_H
