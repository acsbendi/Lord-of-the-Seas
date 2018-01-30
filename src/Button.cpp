//
// Created by Bendi on 1/30/2018.
//

#include "Button.h"
#include "Graphics.h"

const sf::Font Button::font = Graphics::createFont("Garamond Classico SC.ttf");
const sf::Texture Button::texture = Graphics::createTexture("button2.png");

void Button::draw(sf::RenderTarget &target, sf::RenderStates) const {
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
    sf::Text text1{text,font,19};
    text1.setPosition({static_cast<float >(rect.left + 29), static_cast<float >(rect.top + 13)});
    text1.setStyle(sf::Text::Bold);
    text1.setFillColor(sf::Color::Black);
    target.draw(text1);
}

void Button::onClick(int x, int y) const {
    //transforming x and y into local coordinates (inside the button's rect area)
    x = x - rect.left;
    y = y - rect.top;
    if(x > 0 && y > 0 && x < rect.width && y < rect.height &&
       (x+y) > 8 && (y + rect.width - x) > 8 && (x + rect.height - y) > 8 && (rect.width - x + rect.height - y) > 10)
        action();
}

Button::Button(int x, int y, int width, int height, std::string text, std::function<void()> action)
        : rect{x,y,width,height}, text{std::move(text)}, action{std::move(action)} {

}