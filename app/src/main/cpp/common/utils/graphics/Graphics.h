//
// Created by Bendi on 1/30/2018.
//

#ifndef LORD_OF_THE_SEAS_GRAPHICS_H
#define LORD_OF_THE_SEAS_GRAPHICS_H

#include <string>
#include "ResourceManager.hpp"

using std::string;

namespace Graphics{
    inline int CreateTexture(const string& fileName)
    {
        return ResourceManager::GetInstance().CreateNewTexture(fileName);
    }

    inline int CreateFont(const string& fileName){
        return ResourceManager::GetInstance().CreateNewFont(fileName);
    }
}

#endif //LORD_OF_THE_SEAS_GRAPHICS_H
