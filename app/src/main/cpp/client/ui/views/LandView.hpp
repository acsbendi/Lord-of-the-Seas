//
// Created by Bendi on 9/3/2018.
//

#ifndef LORD_OF_THE_SEAS_LANDVIEW_HPP
#define LORD_OF_THE_SEAS_LANDVIEW_HPP

#include "GridSquareView.hpp"

using sf::Texture;

class LandView : public GridSquareView{
public:
    explicit LandView(Position position, shared_ptr<PlayerView> playerView);
    const Texture& GetTexture() const override;

private:
    static const int textureToken;
};


#endif //LORD_OF_THE_SEAS_LANDVIEW_HPP
