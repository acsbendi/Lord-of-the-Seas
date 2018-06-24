//
// Created by Bendi on 1/28/2018.
//

#ifndef LORD_OF_THE_SEAS_TREASURE_H
#define LORD_OF_THE_SEAS_TREASURE_H

#include "GridSquare.h"

class Treasure : public GridSquare{
private:
    static const sf::Texture texture;

public:
    Treasure(int x,int y);
    void draw(sf::RenderTarget& target, sf::RenderStates) const override;
    int GetValue() const override;
    bool IsSea() const override;
    bool IsLand() const override;
    bool CanEnd() const override;
};


#endif //LORD_OF_THE_SEAS_TREASURE_H
