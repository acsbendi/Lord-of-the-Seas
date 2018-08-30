//
// Created by Bendi on 1/28/2018.
//

#ifndef LORD_OF_THE_SEAS_TREASURE_H
#define LORD_OF_THE_SEAS_TREASURE_H

#include "GridSquare.h"

using sf::Texture;

class Treasure : public GridSquare{
public:
    Treasure(int x,int y);

    int GetValue() const override;
    bool IsSea() const override;
    bool IsLand() const override;
    bool CanEnd() const override;
    const Texture& GetTexture() const override;

private:
    static const Texture texture;
};


#endif //LORD_OF_THE_SEAS_TREASURE_H
