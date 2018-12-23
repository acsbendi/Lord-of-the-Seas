//
// Created by Bendi on 12/23/2018.
//

#include "ResourceNotFoundException.h"

ResourceNotFoundException::ResourceNotFoundException(string resourceFileName) :
        resourceFileName{resourceFileName}  {

}

const char* ResourceNotFoundException::what() const {
    string whatMessage = "Resource was not found in location " + resourceFileName;
    return whatMessage.c_str();
}