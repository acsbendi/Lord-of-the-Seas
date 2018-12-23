//
// Created by Bendi on 12/23/2018.
//

#ifndef LORD_OF_THE_SEAS_RESOURCEHOLDER_H
#define LORD_OF_THE_SEAS_RESOURCEHOLDER_H

#include <unordered_map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include "ResourceNotFoundException.h"

using std::unordered_map;
using std::string;
using sf::Texture;

class ResourceHolder {
public:
    ResourceHolder(const ResourceHolder&) = delete;
    void operator=(const ResourceHolder&) = delete;
    ResourceHolder& GetInstance();
    Texture& GetTexture(int token);
    int CreateNewTexture(string fileName);

private:
    ResourceHolder();

    int currentToken;
    unordered_map<int, Texture> textures;
};


#endif //LORD_OF_THE_SEAS_RESOURCEHOLDER_H
