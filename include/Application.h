//
// Created by Bendi on 1/28/2018.
//

#ifndef LORD_OF_THE_SEAS_APPLICATION_H
#define LORD_OF_THE_SEAS_APPLICATION_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.h"

using std::vector;
using sf::RenderWindow;
using sf::Texture;

class Application {
private:
    static const int WIDTH = 400;
    static const int HEIGHT = 400;
    static const Texture background;
    bool end;
    RenderWindow window;
    vector<Button> buttons;

    void StartNewLocalGame();
    void StartNewOnlineGame();
    void Exit();
    void ShowScores(int scoreOfPlayer1, int scoreOfPlayer2);
    void Refresh();

public:
    Application();
    void Start();
};


#endif //LORD_OF_THE_SEAS_APPLICATION_H
