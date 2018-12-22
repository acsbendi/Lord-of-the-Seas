//
// Created by Bendi on 9/3/2018.
//

#ifndef LORD_OF_THE_SEAS_TREASUREVIEW_HPP
#define LORD_OF_THE_SEAS_TREASUREVIEW_HPP

#include "GridSquareView.hpp"

using sf::Texture;

class TreasureView : public GridSquareView {
public:
    explicit TreasureView(Position position, shared_ptr<PlayerView> playerView);
    const Texture& GetTexture() const override;

private:
    static const Texture texture;
};

#endif //LORD_OF_THE_SEAS_TREASUREVIEW_HPP
