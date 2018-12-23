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
    textures.emplace(currentTextureToken, Texture{});
    bool result = textures.at(currentFontToken).loadFromFile(fileName);
    if(!result)
        throw ResourceNotFoundException{fileName};

    return currentTextureToken++;
}

Font& ResourceManager::GetFont(int token) {
    return fonts.at(token);
}

int ResourceManager::CreateNewFont(const string& fileName) {
    fonts.emplace(currentFontToken, Font{});
    bool result = fonts.at(currentFontToken).loadFromFile(fileName);
    if(!result)
        throw ResourceNotFoundException{fileName};

    return currentFontToken++;
}
