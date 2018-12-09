//
// Created by Bendi on 1/30/2018.
//

#include "Button.h"
#include "Graphics.h"

#include <iostream>

using std::move;
using sf::Color;

const Font Button::font = Graphics::CreateFont("Garamond Classico SC.ttf");
const Texture Button::texture = Graphics::CreateTexture("button2.png");

void Button::draw(RenderTarget &target, RenderStates) const {
    ShowTexture(target);
    ShowText(target);
}

void Button::ShowTexture(RenderTarget &target) const {
    Sprite background;
    SetBackgroundProperties(background);
    target.draw(background);
}

void Button::ShowText(RenderTarget& target) const {
    target.draw(text);
}

void Button::OnClick(int, int) const {
    DoActionIfSelected();
}

Button::Button(int x, int y, int width, int height, const string& text, function<void()> action)
        : rect{x,y,width,height}, text{text,font}, action{move(action)}, selected{false} {
    SetTextProperties();
}

bool Button::OnMouseMove(int x, int y) {
    TransformIntoLocalCoordinates(x,y);
    selected = x > 0 && y > 0 && x < rect.width && y < rect.height &&
       (x+y) > 8 && (y + rect.width - x) > 8 && (x + rect.height - y) > 8 && (rect.width - x + rect.height - y) > 10;
    return selected;
}

void Button::TransformIntoLocalCoordinates(int& x, int& y) const{
    x = x - rect.left;
    y = y - rect.top;
}

void Button::SetTextProperties() {
    text.setCharacterSize(19);
    text.setPosition({static_cast<float >(rect.left + 29), static_cast<float >(rect.top + 13)});
    text.setStyle(Text::Bold);
    text.setColor(Color::Black);
}

void Button::SetBackgroundProperties(Sprite& background) const {
    background.setTexture(texture);
    background.setPosition({static_cast<float >(rect.left), static_cast<float >(rect.top)});
    if(selected)
        background.move(-20,-5);
    background.setScale({rect.width / background.getLocalBounds().width ,rect.height / background.getLocalBounds().height });
    if(selected)
        background.scale(1.2,1.2);
}

void Button::OnEnterPressed() const {
    DoActionIfSelected();
}

void Button::DoActionIfSelected() const {
    if(selected)
        action();
}

