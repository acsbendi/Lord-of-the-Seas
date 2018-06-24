//
// Created by Bendi on 1/28/2018.
//

#ifndef LORD_OF_THE_SEAS_WATER_H
#define LORD_OF_THE_SEAS_WATER_H

#include "GridSquare.h"

class Water : public GridSquare{
private:
    static sf::Texture texture;

public:
    Water(int x,int y);

    void draw(sf::RenderTarget& target, sf::RenderStates) const override;
    int GetValue() const override;
    bool IsSea() const override;
    bool IsLand() const override;
    bool CanEnd() const override;
};


#endif //LORD_OF_THE_SEAS_WATER_H
