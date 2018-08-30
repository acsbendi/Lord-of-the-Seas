//
// Created by Bendi on 1/31/2018.
//

#ifndef LORD_OF_THE_SEAS_ONLINEGAME_H
#define LORD_OF_THE_SEAS_ONLINEGAME_H

#include <SFML/Network.hpp>
#include "Game.h"
#include "ILocalPlayerObserver.h"

using sf::TcpSocket;
using std::vector;
using std::string;

/**
 * @brief The class that manages the online game mode, communicates with the server,
 * and gives input to the Player instance that represents the remote player,
 * instead of the Map (local window) object.
 */
class OnlineGame : public Game, public ILocalPlayerObserver{
public:
    OnlineGame();
    void PlayGame(int &scoreOfPlayer1, int &scoreOfPlayer2) override;
    void OnMove(Direction direction) override;
    void OnTurnEnd() override;
    void OnConfirmation(bool confirmed) override;

private:
    TcpSocket socket;

    /**
     * @brief Waits for the remote player's move and notifies the Player instance that
     * represents the remote player.
     */
    void GetRemoteMove();
    /**
     * @brief Checks if the server has sent messages and returns them in a vector.
     * @return The vector containing the messages received from the server, empty if no messages were sent.
     */
    vector<int> ReceiveMessages() ;
    /**
     * @brief Sends a text message to the server.
     * @param message The text to be sent.
     */
    void SendText(string message);
    /**
     * @brief Creates a connection to the server.
     */
    void CreateConnection();
    void OnExit() override;
};


#endif //LORD_OF_THE_SEAS_ONLINEGAME_H
