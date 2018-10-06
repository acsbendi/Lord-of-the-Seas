//
// Created by Bendi on 9/3/2018.
//

#ifndef LORD_OF_THE_SEAS_GRIDSQUAREVIEW_HPP
#define LORD_OF_THE_SEAS_GRIDSQUAREVIEW_HPP

#include "SFML/Graphics.hpp"
#include "../../../common/gamecore/IGridSquareObserver.hpp"

using sf::Drawable;
using sf::Drawable;
using sf::Vector2i;
using sf::RenderTarget;
using sf::Texture;
using sf::RenderStates;
using sf::Vertex;

class GridSquare;
struct Edge;

class GridSquareView : public Drawable, public IGridSquareObserver {
public:
    void draw(RenderTarget& target, RenderStates) const override;
    virtual const Texture& GetTexture() const = 0;

protected:
    GridSquareView(int x, int y, const GridSquare& gridSquare);

private:
    const Vector2i coordinates;
    const GridSquare& gridSquare;

    void DrawGridSquare(RenderTarget& target) const;
    void DrawTexture(const Texture&, RenderTarget&) const;
    void DrawEdge(const Edge& edge, RenderTarget&) const;
    void ColorEdge(Vertex*, const Edge&) const;
};


#endif //LORD_OF_THE_SEAS_GRIDSQUAREVIEW_HPP
