//
// Created by Bendi on 6/24/2018.
//

#ifndef LORD_OF_THE_SEAS_IMAPOBSERVER_HPP
#define LORD_OF_THE_SEAS_IMAPOBSERVER_HPP

class Map;

class IMapObserver {
public:
    virtual void Update(Map&) = 0;
    virtual ~IMapObserver() = default;
};


#endif //LORD_OF_THE_SEAS_IMAPOBSERVER_HPP
