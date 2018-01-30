//
// Created by Bendi on 1/30/2018.
//

#ifndef LORD_OF_THE_SEAS_GRAPHICS_H
#define LORD_OF_THE_SEAS_GRAPHICS_H

#include <SFML/Graphics.hpp>

namespace Graphics{
    inline sf::Texture createTexture(const std::string& fileName)
    {
        sf::Texture texture;
        texture.loadFromFile(fileName);
        return texture;
    }

    inline const sf::Font createFont(const std::string& fileName){
        sf::Font font;
        font.loadFromFile(fileName);
        return font;
    }
}

#endif //LORD_OF_THE_SEAS_GRAPHICS_H
