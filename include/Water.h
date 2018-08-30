//
// Created by Bendi on 1/28/2018.
//

#ifndef LORD_OF_THE_SEAS_WATER_H
#define LORD_OF_THE_SEAS_WATER_H

#include "GridSquare.h"

using sf::Texture;

class Water : public GridSquare{
public:
    Water(int x,int y);
    int GetValue() const override;
    bool IsSea() const override;
    bool IsLand() const override;
    bool CanEnd() const override;
    const Texture& GetTexture() const override;

private:
    static const Texture texture;
};


#endif //LORD_OF_THE_SEAS_WATER_H
