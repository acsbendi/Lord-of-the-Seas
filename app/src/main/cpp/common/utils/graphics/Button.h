//
// Created by Bendi on 1/30/2018.
//

#ifndef LORD_OF_THE_SEAS_BUTTON_H
#define LORD_OF_THE_SEAS_BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>

using std::string;
using std::function;
using sf::IntRect;
using sf::Font;
using sf::Texture;
using sf::RenderTarget;
using sf::RenderStates;
using sf::Drawable;
using sf::Text;
using sf::Sprite;

class Button : public Drawable{
public:
    Button(int x, int y, int width, int height, const string& text, function<void()> action);
    void draw(RenderTarget& target, RenderStates) const override;
    void OnClick(int x, int y) const;
    bool OnMouseMove(int x, int y);
    void OnEnterPressed() const;

private:
    const function<void()> action;
    const IntRect rect; ///< The coordinates and dimensions of the button's rectangle's top-left corner.
    static int fontToken;
    static int textureToken;
    bool selected;
    Text text;

    void ShowText(RenderTarget&) const;
    void ShowTexture(RenderTarget&) const;
    void TransformIntoLocalCoordinates(int&,int&) const;
    void SetTextProperties(const string& string,const Font& font);
    void SetBackgroundProperties(Sprite&) const;
    void DoActionIfSelected() const;
};



#endif //LORD_OF_THE_SEAS_BUTTON_H
