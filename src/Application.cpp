//
// Created by Bendi on 1/28/2018.
//

#include "Application.h"
#include "Game.h"
#include "Graphics.h"
#include "ScoreDisplay.h"
#include "OnlineGame.h"

const sf::Texture Application::background = Graphics::CreateTexture("menu-background.png");

Application::Application() : window{sf::VideoMode(WIDTH,HEIGHT),"Lord of the Seas"}, end{false} {
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
    sf::Event event{};
    while(!end) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed)
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        Exit();
                        break;
                    case sf::Keyboard::Return:
                        break;
                    default:
                        break;
                }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                for (const Button& button : buttons)
                    button.OnClick(event.mouseButton.x, event.mouseButton.y);
            } else if(event.type == sf::Event::MouseMoved){
                for (Button& button : buttons)
                    button.OnMouseMove(event.mouseMove.x, event.mouseMove.y);
                Refresh();
            } else if (event.type == sf::Event::Closed) {
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
    sf::Sprite sprite;
    sprite.setTexture(background);
    window.draw(sprite);

    for (const Button& button : buttons)
            window.draw(button);

    window.display();
}