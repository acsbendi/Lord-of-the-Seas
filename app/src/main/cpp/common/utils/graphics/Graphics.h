//
// Created by Bendi on 1/30/2018.
//

#ifndef LORD_OF_THE_SEAS_GRAPHICS_H
#define LORD_OF_THE_SEAS_GRAPHICS_H

#include <string>
#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"

using std::string;
using sf::Texture;
using sf::Font;

namespace Graphics{
    inline int CreateTexture(const string& fileName)
    {
        return ResourceManager::GetInstance().CreateNewTexture(fileName);
    }

    inline const Font CreateFont(const string& fileName){
        Font font;
        font.loadFromFile(fileName);
        return font;
    }
}

#endif //LORD_OF_THE_SEAS_GRAPHICS_H
