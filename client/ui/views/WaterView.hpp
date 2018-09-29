//
// Created by Bendi on 9/3/2018.
//

#ifndef LORD_OF_THE_SEAS_WATERVIEW_HPP
#define LORD_OF_THE_SEAS_WATERVIEW_HPP

#include "GridSquareView.hpp"

using sf::Texture;

class WaterView : public GridSquareView {
public:
    WaterView(int x, int y, const GridSquare& gridSquare);
    const Texture& GetTexture() const override;

private:
    static const Texture texture;
};


#endif //LORD_OF_THE_SEAS_WATERVIEW_HPP
