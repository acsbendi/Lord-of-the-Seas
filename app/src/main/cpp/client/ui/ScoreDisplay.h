//
// Created by Bendi on 1/30/2018.
//

#ifndef LORD_OF_THE_SEAS_SCOREDISPLAY_H
#define LORD_OF_THE_SEAS_SCOREDISPLAY_H

#include <SFML/Graphics.hpp>
#include "../../common/utils/graphics/Button.h"

using sf::Text;
using sf::RenderWindow;
using sf::Font;
using sf::Texture;
using sf::Event;

class ScoreDisplay{
public:
    ScoreDisplay(int scoreOfPlayer1,int scoreOfPlayer2);
    void Show();
    void Refresh();

private:
    static constexpr int WIDTH = 400;
    static constexpr int HEIGHT = 400;
    static constexpr int TEXT_X = 165;
    static constexpr int TEXT_SIZE = 20;

    bool end;
    Button okButton;
    RenderWindow window;
    static int fontToken;
    static int backgroundTextureToken;
    Text text1;
    Text text2;
    const int scoreOfPlayer1;
    const int scoreOfPlayer2;

    void InitializeText(Text& text, const string& string, const Font& font);
    void Exit();
    void HandleEvent(const Event&);
    void HandleKeyPress(const Event&);
    void ShowBackgroundAndOkButton();
    void ShowText();
    void SetTextPosition();
    void SetTextStyleAndColor();
};


#endif //LORD_OF_THE_SEAS_SCOREDISPLAY_H
