//
// Created by Bendi on 1/30/2018.
//

#ifndef LORD_OF_THE_SEAS_SCOREDISPLAY_H
#define LORD_OF_THE_SEAS_SCOREDISPLAY_H

#include <SFML/Graphics.hpp>
#include "Button.h"

class ScoreDisplay{
private:
    bool end;
    static const int WIDTH = 400;
    static const int HEIGHT = 400;
    static const int TEXT_X = 165;
    Button okButton;
    sf::RenderWindow window;
    static const sf::Font font;
    static const sf::Texture background;
    sf::Text text1;
    sf::Text text2;

    void exit();
public:
    ScoreDisplay(int scoreOfPlayer1,int scoreOfPlayer2);
    void show();
};


#endif //LORD_OF_THE_SEAS_SCOREDISPLAY_H
