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

class Button : public Drawable{
public:
    Button(int x, int y, int width, int height, string text, function<void()> action);
    void draw(RenderTarget &target, RenderStates) const override;
    void OnClick(int x, int y) const;
    bool OnMouseMove(int x, int y);

private:
    const function<void()> action;
    const string text;
    const IntRect rect; ///< The coordinates and dimensions of the button's rectangle's top-left corner.
    static const Font font;
    static const Texture texture;
    bool selected;
};



#endif //LORD_OF_THE_SEAS_BUTTON_H
