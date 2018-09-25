//
// Created by Bendi on 9/3/2018.
//

#ifndef LORD_OF_THE_SEAS_LANDVIEW_HPP
#define LORD_OF_THE_SEAS_LANDVIEW_HPP

#include "GridSquareView.hpp"

using sf::Texture;

class LandView : public GridSquareView{
public:
    LandView(int x, int y, const GridSquare& gridSquare);
    const Texture& GetTexture() const override;

private:
    static const Texture texture;
};


#endif //LORD_OF_THE_SEAS_LANDVIEW_HPP
