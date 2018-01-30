//
// Created by Bendi on 1/28/2018.
//

#include "Application.h"
#include "Game.h"
#include <iostream>

const sf::Font Application::Button::font = Application::Button::createFont("Garamond Classico SC.ttf");
const sf::Texture Application::Button::texture = Application::createTexture("button2.png");
const sf::Texture Application::background = Application::createTexture("menu-background.png");

const sf::Font Application::Button::createFont(std::string fileName){
    sf::Font font;
    font.loadFromFile(fileName);
    return font;
}

const sf::Texture Application::createTexture(const std::string& fileName)
{
    sf::Texture texture;
    texture.loadFromFile(fileName);
    return texture;
}

Application::Application() : window{sf::VideoMode(WIDTH,HEIGHT),"Lord of the Seas"}, end{false} {
    buttons.emplace_back(100,50,200,50," LOCAL GAME",[&](){this->startNewLocalGame();});
    buttons.emplace_back(100,125,200,50,"ONLINE GAME",[&](){this->startNewOnlineGame();});
    buttons.emplace_back(100,200,200,50,"          EXIT",[=](){this->exit();});
    refresh();
}

void Application::startNewLocalGame() const {
    int scoreOfPlayer1 = 0;
    int scoreOfPlayer2 = 0;
    Game game;
    game.playGame(scoreOfPlayer1,scoreOfPlayer2);
    showScores(scoreOfPlayer1,scoreOfPlayer2);
}

void Application::startNewOnlineGame() const {

}

void Application::showScores(int scoreOfPlayer1, int scoreOfPlayer2) const {
    std::cout << "First player's score: " << scoreOfPlayer1 << std::endl;
    std::cout << "Second player's score: " << scoreOfPlayer2 << std::endl;
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
            } else if (event.type == sf::Event::Closed) {
                end = true;
                window.close();
                return;
            }
        }
    }
}

void Application::Button::draw(sf::RenderTarget &target, sf::RenderStates) const {
    /*sf::RectangleShape rectangle;
    rectangle.setSize({width,height});
    rectangle.setPosition(coordinates);
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setOutlineThickness(5);
    target.draw(rectangle);*/

    //showing texture
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition({static_cast<float >(rect.left), static_cast<float >(rect.top)});
    sprite.setScale({rect.width / sprite.getLocalBounds().width ,rect.height / sprite.getLocalBounds().height });
    target.draw(sprite);

    //showing text
    sf::Text text1{text,font};
    text1.setPosition({static_cast<float >(rect.left + 29), static_cast<float >(rect.top + 13)});
    text1.setCharacterSize(19);
    text1.setStyle(sf::Text::Bold);
    text1.setFillColor(sf::Color::Black);
    target.draw(text1);
}

Application::Button::Button(int x, int y, int width, int height, std::string text, std::function<void()> action)
        : rect{x,y,width,height}, text{std::move(text)}, action{std::move(action)} {

}

void Application::Button::onClick(int x, int y) const {
    //transforming x and y into local coordinates (inside the button's rect area)
    x = x - rect.left;
    y = y - rect.top;
    if(x > 0 && y > 0 && x < rect.width && y < rect.height &&
       (x+y) > 8 && (y + rect.width - x) > 8 && (x + rect.height - y) > 8 && (rect.width - x + rect.height - y) > 10)
        action();
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