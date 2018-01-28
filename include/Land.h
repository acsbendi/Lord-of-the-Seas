//
// Created by Bendi on 1/28/2018.
//

#ifndef LORD_OF_THE_SEAS_LAND_H
#define LORD_OF_THE_SEAS_LAND_H

#include "GridSquare.h"

class Land : public GridSquare{
private:
    static sf::Texture texture;

public:
    Land(int x,int y);

    void draw(sf::RenderTarget& target, sf::RenderStates) const override;
    int getValue() const override;
    bool isSea() const override;
    bool isLand() const override;
    bool canEnd() const override;

};


#endif //LORD_OF_THE_SEAS_LAND_H
