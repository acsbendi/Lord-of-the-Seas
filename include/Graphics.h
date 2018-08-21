//
// Created by Bendi on 1/30/2018.
//

#ifndef LORD_OF_THE_SEAS_GRAPHICS_H
#define LORD_OF_THE_SEAS_GRAPHICS_H

#include <string>
#include <SFML/Graphics.hpp>

using std::string;
using sf::Texture;
using sf::Font;

namespace Graphics{
    inline Texture CreateTexture(const string& fileName)
    {
        Texture texture;
        texture.loadFromFile(fileName);
        return texture;
    }

    inline const Font CreateFont(const string& fileName){
        Font font;
        font.loadFromFile(fileName);
        return font;
    }
}

#endif //LORD_OF_THE_SEAS_GRAPHICS_H
