//
// Created by Bendi on 1/30/2018.
//

#include "ScoreDisplay.h"
#include "Graphics.h"

using std::to_string;
using sf::Event;
using sf::Keyboard;
using sf::Mouse;
using sf::Sprite;
using sf::Color;
using sf::VideoMode;

const Font ScoreDisplay::font = Graphics::CreateFont("Treamd.ttf");
const Texture ScoreDisplay::background = Graphics::CreateTexture("score-background2.png");

ScoreDisplay::ScoreDisplay(int scoreOfPlayer1, int scoreOfPlayer2) : okButton(100,300,200,50,"           OK",[&](){ this->Exit();}),
                                                                     window{VideoMode(WIDTH,HEIGHT),"Congratulations"}, end{false},
text1{"First player's score: " + to_string(scoreOfPlayer1),font,20}, text2{"Second player's score: " + to_string(scoreOfPlayer2),font,20},
                                                                     scoreOfPlayer1{scoreOfPlayer1}, scoreOfPlayer2{scoreOfPlayer2}
{
    Refresh();
}

void ScoreDisplay::Exit() {
    end = true;
    window.close();
}

void ScoreDisplay::Show(){
    Event event{};
    while(!end) {
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyPressed)
                switch (event.key.code) {
                    case Keyboard::Escape:
                        Exit();
                        break;
                    case Keyboard::Return:
                        Exit();
                        break;
                    default:
                        break;
                }
            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                okButton.OnClick(event.mouseButton.x, event.mouseButton.y);
            } else if(event.type == Event::MouseMoved) {
                okButton.OnMouseMove(event.mouseMove.x, event.mouseMove.y);
                Refresh();
            } else if (event.type == Event::Closed) {
                end = true;
                window.close();
                return;
            }
        }
    }
}

void ScoreDisplay::Refresh(){
    Sprite sprite;
    sprite.setTexture(background);
    window.draw(sprite);
    window.draw(okButton);

    if(scoreOfPlayer1 >= scoreOfPlayer2) {
        text1.setPosition(TEXT_X,50);
        text2.setPosition(TEXT_X,100);
    }
    else{
        text1.setPosition(TEXT_X,100);
        text2.setPosition(TEXT_X,50);
    }
    text1.setStyle(Text::Bold);
    text2.setStyle(Text::Bold);
    text1.setFillColor(Color::Black);
    text2.setFillColor(Color::Black);
    window.draw(text1);
    window.draw(text2);

    window.display();
}