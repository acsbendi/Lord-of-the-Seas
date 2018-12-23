//
// Created by Bendi on 1/30/2018.
//

#include "Button.h"
#include "Graphics.h"
#include "ResourceManager.hpp"

using std::move;
using sf::Color;

int Button::fontToken = -1;
int Button::textureToken = -1;

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
        : action{move(action)}, rect{x,y,width,height}, selected{false}, text{} {
    if(textureToken == -1){
        textureToken = Graphics::CreateTexture("button2.png");
    }
    if(fontToken == -1){
        fontToken = Graphics::CreateFont("Garamond Classico SC.ttf");
    }
    Font& font = ResourceManager::GetInstance().GetFont(fontToken);
    SetTextProperties(text, font);
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

void Button::SetTextProperties(const string& string,const Font& font) {
    text.setString(string);
    text.setFont(font);
    text.setCharacterSize(19);
    text.setPosition({static_cast<float >(rect.left + 29), static_cast<float >(rect.top + 13)});
    text.setStyle(Text::Bold);
    text.setFillColor(Color::Black);
}

void Button::SetBackgroundProperties(Sprite& background) const {
    Texture& texture = ResourceManager::GetInstance().GetTexture(textureToken);
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

