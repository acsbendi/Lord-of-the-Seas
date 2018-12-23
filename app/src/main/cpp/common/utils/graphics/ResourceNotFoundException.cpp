//
// Created by Bendi on 12/23/2018.
//

#include "ResourceNotFoundException.hpp"

ResourceNotFoundException::ResourceNotFoundException(string resourceFileName) :
        message{"Resource was not found in location " + resourceFileName}  {

}

const char* ResourceNotFoundException::what() const noexcept {
    return message.c_str();
}