//
// Created by Bendi on 1/30/2018.
//

#include "ScoreDisplay.h"
#include "Graphics.h"

const sf::Font ScoreDisplay::font = Graphics::createFont("Treamd.ttf");
const sf::Texture ScoreDisplay::background = Graphics::createTexture("score-background2.png");

ScoreDisplay::ScoreDisplay(int scoreOfPlayer1, int scoreOfPlayer2) : okButton(100,300,200,50,"           OK",[&](){this->exit();}),
                                                                     window{sf::VideoMode(WIDTH,HEIGHT),"Congratulations"}, end{false},
text1{"First player's score: " + std::to_string(scoreOfPlayer1),font,20}, text2{"Second player's score: " + std::to_string(scoreOfPlayer2),font,20},
                                                                     scoreOfPlayer1{scoreOfPlayer1}, scoreOfPlayer2{scoreOfPlayer2}
{
    refresh();
}

void ScoreDisplay::exit() {
    end = true;
    window.close();
}

void ScoreDisplay::show(){
    sf::Event event{};
    while(!end) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed)
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        exit();
                        break;
                    case sf::Keyboard::Return:
                        exit();
                        break;
                    default:
                        break;
                }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                okButton.onClick(event.mouseButton.x, event.mouseButton.y);
            } else if(event.type == sf::Event::MouseMoved) {
                okButton.onMouseMove(event.mouseMove.x, event.mouseMove.y);
                refresh();
            } else if (event.type == sf::Event::Closed) {
                end = true;
                window.close();
                return;
            }
        }
    }
}

void ScoreDisplay::refresh(){
    sf::Sprite sprite;
    sprite.setTexture(background);
    window.draw(sprite);
    window.draw(okButton);

    //
    if(scoreOfPlayer1 >= scoreOfPlayer2) {
        text1.setPosition(TEXT_X,50);
        text2.setPosition(TEXT_X,100);
    }
    else{
        text1.setPosition(TEXT_X,100);
        text2.setPosition(TEXT_X,50);
    }
    text1.setStyle(sf::Text::Bold);
    text2.setStyle(sf::Text::Bold);
    text1.setFillColor(sf::Color::Black);
    text2.setFillColor(sf::Color::Black);
    window.draw(text1);
    window.draw(text2);

    window.display();
}