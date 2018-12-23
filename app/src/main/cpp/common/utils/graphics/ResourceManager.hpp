//
// Created by Bendi on 12/23/2018.
//

#ifndef LORD_OF_THE_SEAS_RESOURCEHOLDER_H
#define LORD_OF_THE_SEAS_RESOURCEHOLDER_H

#include <unordered_map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include "ResourceNotFoundException.hpp"

using std::unordered_map;
using std::string;
using sf::Texture;
using sf::Font;

class ResourceManager {
public:
    ResourceManager(const ResourceManager&) = delete;
    void operator=(const ResourceManager&) = delete;
    static ResourceManager& GetInstance();
    Texture& GetTexture(int token);
    int CreateNewTexture(const string& fileName);
    Font& GetFont(int token);
    int CreateNewFont(const string& fileName);

private:
    ResourceManager();

    int currentTextureToken;
    int currentFontToken;
    unordered_map<int, Texture> textures;
    unordered_map<int, Font> fonts;
};


#endif //LORD_OF_THE_SEAS_RESOURCEHOLDER_H
