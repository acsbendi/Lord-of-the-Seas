//
// Created by Bendi on 1/28/2018.
//

#include "Application.h"
#include "Game.h"
#include "Graphics.h"
#include "ScoreDisplay.h"
#include "OnlineGame.h"

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
    window.setVisible(false);
    int scoreOfPlayer1 = 0;
    int scoreOfPlayer2 = 0;
    Game game;
    game.PlayGame(scoreOfPlayer1, scoreOfPlayer2);
    if(scoreOfPlayer1 != 0 || scoreOfPlayer2 != 0)
        ShowScores(scoreOfPlayer1, scoreOfPlayer2);
    window.setVisible(true);
    Refresh();
}

void Application::StartNewOnlineGame(){
    window.setVisible(false);
    int scoreOfPlayer1 = 0;
    int scoreOfPlayer2 = 0;
    OnlineGame onlineGame;
    onlineGame.PlayGame(scoreOfPlayer1, scoreOfPlayer2);
    if(scoreOfPlayer1 != 0 || scoreOfPlayer2 != 0)
        ShowScores(scoreOfPlayer1, scoreOfPlayer2);
    window.setVisible(true);
    Refresh();
}

void Application::ShowScores(int scoreOfPlayer1, int scoreOfPlayer2){
    ScoreDisplay scoreDisplay(scoreOfPlayer1,scoreOfPlayer2);
    scoreDisplay.Show();
}

void Application::Start() {
    Event event{};
    while(!end) {
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyPressed)
                switch (event.key.code) {
                    case Keyboard::Escape:
                        Exit();
                        break;
                    case Keyboard::Return:
                        break;
                    default:
                        break;
                }
            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                for (const Button& button : buttons)
                    button.OnClick(event.mouseButton.x, event.mouseButton.y);
            } else if(event.type == Event::MouseMoved){
                for (Button& button : buttons)
                    button.OnMouseMove(event.mouseMove.x, event.mouseMove.y);
                Refresh();
            } else if (event.type == Event::Closed) {
                end = true;
                window.close();
                return;
            }
        }
    }
}

void Application::Exit() {
    end = true;
    window.close();
}

void Application::Refresh()
{
    window.clear();
    Sprite sprite;
    sprite.setTexture(background);
    window.draw(sprite);

    for (const Button& button : buttons)
            window.draw(button);

    window.display();
}