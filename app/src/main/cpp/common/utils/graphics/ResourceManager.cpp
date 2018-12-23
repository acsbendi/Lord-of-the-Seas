//
// Created by Bendi on 12/23/2018.
//

#include "ResourceManager.hpp"

ResourceManager& ResourceManager::GetInstance() {
    static ResourceManager instance;
    return instance;
}

ResourceManager::ResourceManager() :
        textures{}, fonts{} {
    currentTextureToken = 0;
    currentFontToken = 0;
}

Texture& ResourceManager::GetTexture(int token) {
    return textures.at(token);
}

int ResourceManager::CreateNewTexture(const string& fileName) {
    Texture texture{};
    bool result = texture.loadFromFile(fileName);
    if(!result)
        throw ResourceNotFoundException{fileName};

    textures.emplace(currentTextureToken, texture);
    return currentTextureToken++;
}

Font& ResourceManager::GetFont(int token) {
    return fonts.at(token);
}

int ResourceManager::CreateNewFont(const string& fileName) {
    Font font{};
    bool result = font.loadFromFile(fileName);
    if(!result)
        throw ResourceNotFoundException{fileName};

    fonts.emplace(currentFontToken, font);
    return currentFontToken++;
}
