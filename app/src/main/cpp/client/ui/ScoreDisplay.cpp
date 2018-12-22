//
// Created by Bendi on 1/30/2018.
//

#include "ScoreDisplay.h"
#include "../../common/utils/graphics/Graphics.h"

using std::to_string;
using sf::Event;
using sf::Keyboard;
using sf::Mouse;
using sf::Sprite;
using sf::Color;
using sf::VideoMode;

const Font ScoreDisplay::font = Graphics::CreateFont("Treamd.ttf");
const Texture ScoreDisplay::background = Graphics::CreateTexture("score-background2.png");

ScoreDisplay::ScoreDisplay(int scoreOfPlayer1, int scoreOfPlayer2) :
        end{false}, okButton(100,300,200,50,"           OK",[&](){ this->Exit();}),
        window{VideoMode(WIDTH,HEIGHT),"Congratulations"},
        text1{"First player's score: " + to_string(scoreOfPlayer1),font,20},
        text2{"Second player's score: " + to_string(scoreOfPlayer2),font,20},
        scoreOfPlayer1{scoreOfPlayer1}, scoreOfPlayer2{scoreOfPlayer2}
{
    Refresh();
}

void ScoreDisplay::Show(){
    Event event{};
    while(!end) {
        while (window.pollEvent(event)) {
            HandleEvent(event);
        }
    }
}

void ScoreDisplay::HandleEvent(const Event& event) {
    switch (event.type){
        case Event::KeyPressed:
            HandleKeyPress(event);
            break;
        case Event::MouseButtonPressed:
            if(event.mouseButton.button == Mouse::Left)
                okButton.OnClick(event.mouseButton.x, event.mouseButton.y);
            break;
        case Event::MouseMoved:
            okButton.OnMouseMove(event.mouseMove.x, event.mouseMove.y);
            Refresh();
            break;
        case Event::Closed:
            Exit();
            break;
        default:
            break;
    }
}

void ScoreDisplay::HandleKeyPress(const Event& event) {
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
}

void ScoreDisplay::Refresh(){
    ShowBackgroundAndOkButton();
    ShowText();
    window.display();
}

void ScoreDisplay::ShowBackgroundAndOkButton() {
    Sprite sprite;
    sprite.setTexture(background);
    window.draw(sprite);
    window.draw(okButton);
}

void ScoreDisplay::ShowText(){
    SetTextPosition();
    SetTextStyleAndColor();
    window.draw(text1);
    window.draw(text2);
}

void ScoreDisplay::SetTextPosition() {
    if(scoreOfPlayer1 >= scoreOfPlayer2) {
        text1.setPosition(TEXT_X,50);
        text2.setPosition(TEXT_X,100);
    }
    else{
        text1.setPosition(TEXT_X,100);
        text2.setPosition(TEXT_X,50);
    }
}

void ScoreDisplay::SetTextStyleAndColor() {
    text1.setStyle(Text::Bold);
    text2.setStyle(Text::Bold);
    text1.setFillColor(Color::Black);
    text2.setFillColor(Color::Black);
}

void ScoreDisplay::Exit() {
    end = true;
    window.close();
}
