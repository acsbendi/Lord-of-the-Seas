//
// Created by Bendi on 1/30/2018.
//

#include "Button.h"
#include "Graphics.h"

#include <iostream>

using sf::Sprite;
using sf::Text;
using sf::Color;

const Font Button::font = Graphics::CreateFont("Garamond Classico SC.ttf");
const Texture Button::texture = Graphics::CreateTexture("button2.png");

void Button::draw(RenderTarget &target, RenderStates) const {
    //showing texture
    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition({static_cast<float >(rect.left), static_cast<float >(rect.top)});
    if(selected)
        sprite.move(-20,-5);
    sprite.setScale({rect.width / sprite.getLocalBounds().width ,rect.height / sprite.getLocalBounds().height });
    if(selected)
        sprite.scale(1.2,1.2);
    target.draw(sprite);

    //showing text
    Text text1{text,font,19};
    text1.setPosition({static_cast<float >(rect.left + 29), static_cast<float >(rect.top + 13)});
    text1.setStyle(Text::Bold);
    text1.setFillColor(Color::Black);
    target.draw(text1);
}

void Button::OnClick(int, int) const {
    if(selected)
        action();
}

Button::Button(int x, int y, int width, int height, string text, function<void()> action)
        : rect{x,y,width,height}, text{std::move(text)}, action{std::move(action)}, selected{false} {

}

bool Button::OnMouseMove(int x, int y) {
    //transforming x and y into local coordinates (inside the button's rect area)
    x = x - rect.left;
    y = y - rect.top;
    selected = x > 0 && y > 0 && x < rect.width && y < rect.height &&
       (x+y) > 8 && (y + rect.width - x) > 8 && (x + rect.height - y) > 8 && (rect.width - x + rect.height - y) > 10;
    return selected;
}
