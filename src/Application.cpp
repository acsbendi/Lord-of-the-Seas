//
// Created by Bendi on 1/28/2018.
//

#include "Application.h"
#include "Game.h"
#include "Graphics.h"
#include "ScoreDisplay.h"

const sf::Texture Application::background = Graphics::createTexture("menu-background.png");

Application::Application() : window{sf::VideoMode(WIDTH,HEIGHT),"Lord of the Seas"}, end{false} {
    buttons.emplace_back(100,50,200,50," LOCAL GAME",[&](){this->startNewLocalGame();});
    buttons.emplace_back(100,125,200,50,"ONLINE GAME",[&](){this->startNewOnlineGame();});
    buttons.emplace_back(100,200,200,50,"          EXIT",[&](){this->exit();});
    refresh();
}

void Application::startNewLocalGame(){
    window.setVisible(false);
    int scoreOfPlayer1 = 0;
    int scoreOfPlayer2 = 0;
    Game game;
    game.playGame(scoreOfPlayer1,scoreOfPlayer2);
    if(scoreOfPlayer1 != 0 || scoreOfPlayer2 != 0)
        showScores(scoreOfPlayer1,scoreOfPlayer2);
    window.setVisible(true);
    refresh();
}

void Application::startNewOnlineGame(){

}

void Application::showScores(int scoreOfPlayer1, int scoreOfPlayer2){
    ScoreDisplay scoreDisplay(scoreOfPlayer1,scoreOfPlayer2);
    scoreDisplay.show();
}

void Application::start() {
    sf::Event event{};
    while(!end) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed)
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        exit();
                        break;
                    case sf::Keyboard::Return:
                        break;
                    default:
                        break;
                }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                for (const Button& button : buttons)
                    button.onClick(event.mouseButton.x, event.mouseButton.y);
            } else if(event.type == sf::Event::MouseMoved){
                for (Button& button : buttons)
                    button.onMouseMove(event.mouseMove.x, event.mouseMove.y);
                refresh();
            } else if (event.type == sf::Event::Closed) {
                end = true;
                window.close();
                return;
            }
        }
    }
}

void Application::exit() {
    end = true;
    window.close();
}

void Application::refresh()
{
    window.clear();
    sf::Sprite sprite;
    sprite.setTexture(background);
    window.draw(sprite);

    for (const Button& button : buttons)
            window.draw(button);

    window.display();
}