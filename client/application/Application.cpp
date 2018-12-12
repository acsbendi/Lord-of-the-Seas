//
// Created by Bendi on 1/28/2018.
//

#include <iostream>

#include "Application.h"
#include "../games/Game.h"
#include "../../common/utils/graphics/Graphics.h"
#include "../ui/ScoreDisplay.h"
#include "../games/OnlineGame.h"
#include "../../common/gamecore/MapBuilder.hpp"

using std::move;
using std::make_unique;
using sf::VideoMode;
using sf::Event;
using sf::Keyboard;
using sf::Mouse;
using sf::Sprite;

const Texture Application::background = Graphics::CreateTexture("menu-background.png");

Application::Application() : window{VideoMode(WIDTH,HEIGHT),"Lord of the Seas"}, end{false} {
    buttons.emplace_back(100,50,200,50," LOCAL GAME",[&](){ this->StartNewLocalGame();});
    buttons.emplace_back(100,125,200,50,"ONLINE GAME",[&](){ this->StartNewOnlineGame();});
    buttons.emplace_back(100,200,200,50,"          EXIT",[&](){ this->Exit();});
    Refresh();
}

void Application::StartNewLocalGame(){
    StartNewGame(Game{MapBuilder{}});
}

void Application::StartNewOnlineGame(){
    StartNewGame(OnlineGame{MapBuilder{}});
}

void Application::StartNewGame(Game&& game) {
    window.setVisible(false);
    PlayGameAndShowResults(move(game));
    window.setVisible(true);
    Refresh();
}

void Application::PlayGameAndShowResults(Game&& game) {
    int scoreOfPlayer1 = 0;
    int scoreOfPlayer2 = 0;
    game.PlayGame(scoreOfPlayer1, scoreOfPlayer2);
    if(scoreOfPlayer1 != 0 || scoreOfPlayer2 != 0)
        ShowScores(scoreOfPlayer1, scoreOfPlayer2);
}

void Application::ShowScores(int scoreOfPlayer1, int scoreOfPlayer2){
    ScoreDisplay scoreDisplay(scoreOfPlayer1,scoreOfPlayer2);
    scoreDisplay.Show();
}

void Application::Start() {
    Event event{};
    while(!end) {
        while (window.pollEvent(event)) {
            HandleEvent(event);
        }
    }
}

void Application::HandleEvent(const Event& event) {
    switch (event.type){
        case Event::KeyPressed:
            HandleKeyPressedEvent(event);
            break;
        case Event::MouseButtonPressed:
            if(event.mouseButton.button == Mouse::Left)
                NotifyButtonsOnLeftMouseButtonPressed(event);
            break;
        case Event::MouseMoved:
            HandleMouseMovedEvent(event);
            break;
        case Event::Closed:
            HandleClosedEvent(event);
            break;
        default:
            break;
    }
}

void Application::HandleKeyPressedEvent(const Event& event) {
    switch (event.key.code) {
        case Keyboard::Escape:
            Exit();
            break;
        case Keyboard::Return:
            NotifyButtonsOnEnterPressed();
            break;
        default:
            break;
    }
}

void Application::NotifyButtonsOnLeftMouseButtonPressed(const Event& event) {
    for (const Button& button : buttons)
        button.OnClick(event.mouseButton.x, event.mouseButton.y);
}

void Application::HandleMouseMovedEvent(const Event& event) {
    NotifyButtonsOnMouseMoved(event);
    Refresh();
}

void Application::NotifyButtonsOnMouseMoved(const Event& event) {
    for (Button& button : buttons)
        button.OnMouseMove(event.mouseMove.x, event.mouseMove.y);
}

void Application::HandleClosedEvent(const Event&) {
    end = true;
    window.close();
}

void Application::Exit() {
    end = true;
    window.close();
}

void Application::Refresh()
{
    window.clear();
    DrawElements();
    window.display();
}

void Application::DrawElements() {
    DrawBackground();
    DrawButtons();
}

void Application::DrawBackground() {
    Sprite sprite;
    sprite.setTexture(background);
    window.draw(sprite);
}

void Application::DrawButtons(){
    for (const Button& button : buttons)
        window.draw(button);
}

void Application::NotifyButtonsOnEnterPressed() const {
    for (const Button& button : buttons)
        button.OnEnterPressed();
}