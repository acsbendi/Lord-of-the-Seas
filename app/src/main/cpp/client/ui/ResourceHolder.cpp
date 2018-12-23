//
// Created by Bendi on 12/23/2018.
//

#include "ResourceHolder.h"

ResourceHolder& ResourceHolder::GetInstance() {
    static ResourceHolder instance;
    return instance;
}

ResourceHolder::ResourceHolder() :
        textures{} {
    currentToken = 0;
}

Texture& ResourceHolder::GetTexture(int token) {
    return textures.at(token);
}

int ResourceHolder::CreateNewTexture(string fileName) {
    Texture texture{};
    bool result = texture.loadFromFile(fileName);
    if(!result)
        throw ResourceNotFoundException{fileName};

    textures.emplace(currentToken++, texture);
    return currentToken;
}

