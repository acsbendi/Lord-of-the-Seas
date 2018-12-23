//
// Created by Bendi on 12/23/2018.
//

#ifndef LORD_OF_THE_SEAS_RESOURCEHOLDER_H
#define LORD_OF_THE_SEAS_RESOURCEHOLDER_H

#include <unordered_map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include "ResourceNotFoundException.hpp"

using std::unordered_map;
using std::string;
using sf::Texture;

class ResourceManager {
public:
    ResourceManager(const ResourceManager&) = delete;
    void operator=(const ResourceManager&) = delete;
    ResourceManager& GetInstance();
    Texture& GetTexture(int token);
    int CreateNewTexture(string fileName);

private:
    ResourceManager();

    int currentToken;
    unordered_map<int, Texture> textures;
};


#endif //LORD_OF_THE_SEAS_RESOURCEHOLDER_H
