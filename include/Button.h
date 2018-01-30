//
// Created by Bendi on 1/30/2018.
//

#ifndef LORD_OF_THE_SEAS_BUTTON_H
#define LORD_OF_THE_SEAS_BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>

class Button : public sf::Drawable{
private:
    const std::function<void()> action;
    const std::string text;
    const sf::IntRect rect; ///< The coordinates and dimensions of the button's rectangle's top-left corner.
    static const sf::Font font;
    static const sf::Texture texture;
    bool selected;
public:
    Button(int x, int y, int width, int height, std::string text, std::function<void()> action);

    void draw(sf::RenderTarget &target, sf::RenderStates) const override;
    void onClick(int x, int y) const;
    bool onMouseMove(int x, int y);
};



#endif //LORD_OF_THE_SEAS_BUTTON_H
