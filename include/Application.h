//
// Created by Bendi on 1/28/2018.
//

#ifndef LORD_OF_THE_SEAS_APPLICATION_H
#define LORD_OF_THE_SEAS_APPLICATION_H

#include <SFML/Graphics.hpp>
#include "Button.h"

class Application {
private:
    static const int WIDTH = 400;
    static const int HEIGHT = 400;
    static const sf::Texture background;
    bool end;
    sf::RenderWindow window;
    std::vector<Button> buttons;

    void startNewLocalGame();
    void startNewOnlineGame();
    void exit();
    void showScores(int scoreOfPlayer1,int scoreOfPlayer2);
    void refresh();

public:
    Application();
    void start();
};


#endif //LORD_OF_THE_SEAS_APPLICATION_H
