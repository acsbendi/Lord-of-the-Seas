//
// Created by Bendi on 1/31/2018.
//

#ifndef LORD_OF_THE_SEAS_ONLINEGAME_H
#define LORD_OF_THE_SEAS_ONLINEGAME_H

#include <SFML/Network.hpp>
#include "Game.h"
#include "ILocalPlayerObserver.h"

class OnlineGame : public Game, public ILocalPlayerObserver{
private:
    sf::TcpSocket socket;

    void getRemoteMove();
    std::string receiveText();
    void sendText(std::string message);
    void createConnection();
    void onExit() override;
public:
    OnlineGame();
    void playGame(int &scoreOfPlayer1, int &scoreOfPlayer2) override;
    void onMove(Direction direction) override;
    void onTurnEnd() override;
    void onConfirmation(bool confirmed) override;
};


#endif //LORD_OF_THE_SEAS_ONLINEGAME_H
