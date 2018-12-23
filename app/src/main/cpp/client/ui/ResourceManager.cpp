//
// Created by Bendi on 12/23/2018.
//

#include "ResourceManager.hpp"

ResourceManager& ResourceManager::GetInstance() {
    static ResourceManager instance;
    return instance;
}

ResourceManager::ResourceManager() :
        textures{} {
    currentToken = 0;
}

Texture& ResourceManager::GetTexture(int token) {
    return textures.at(token);
}

int ResourceManager::CreateNewTexture(string fileName) {
    Texture texture{};
    bool result = texture.loadFromFile(fileName);
    if(!result)
        throw ResourceNotFoundException{fileName};

    textures.emplace(currentToken++, texture);
    return currentToken;
}

