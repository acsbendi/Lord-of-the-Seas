//
// Created by Bendi on 1/28/2018.
//

#include "Application.h"
#include "Game.h"
#include "Graphics.h"
#include "ScoreDisplay.h"
#include "OnlineGame.h"

using std::move;
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
    StartNewGame(Game{});
}

void Application::StartNewOnlineGame(){
    StartNewGame(OnlineGame{});
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
    if (event.type == Event::KeyPressed)
        HandleKeyPressedEvent(event);
    else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        HandleLeftMouseButtonPressedEvent(event);
    else if(event.type == Event::MouseMoved)
        HandleMouseMovedEvent(event);
    else if (event.type == Event::Closed)
        HandleClosedEvent(event);
}

void Application::HandleKeyPressedEvent(const Event& event) {
    switch (event.key.code) {
        case Keyboard::Escape:
            Exit();
            break;
        case Keyboard::Return:
            break;
        default:
            break;
    }
}

void Application::HandleLeftMouseButtonPressedEvent(const Event& event) {
    for (const Button& button : buttons)
        button.OnClick(event.mouseButton.x, event.mouseButton.y);
}

void Application::HandleMouseMovedEvent(const Event& event) {
    for (Button& button : buttons)
        button.OnMouseMove(event.mouseMove.x, event.mouseMove.y);
    Refresh();
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