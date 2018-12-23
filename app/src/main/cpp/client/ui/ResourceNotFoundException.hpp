//
// Created by Bendi on 12/23/2018.
//

#ifndef LORD_OF_THE_SEAS_RESOURCENOTFOUNDEXCEPTION_H
#define LORD_OF_THE_SEAS_RESOURCENOTFOUNDEXCEPTION_H

#include <exception>
#include <string>

using std::exception;
using std::string;

class ResourceNotFoundException : public exception{
public:
    ResourceNotFoundException(string resourceFileName);
    const char* what() const override;

private:
    string message;
};


#endif //LORD_OF_THE_SEAS_RESOURCENOTFOUNDEXCEPTION_H
