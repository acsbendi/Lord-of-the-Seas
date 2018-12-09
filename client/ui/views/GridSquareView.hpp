//
// Created by Bendi on 9/3/2018.
//

#ifndef LORD_OF_THE_SEAS_GRIDSQUAREVIEW_HPP
#define LORD_OF_THE_SEAS_GRIDSQUAREVIEW_HPP

#include <memory>
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "../../../common/gamecore/Position.hpp"
#include "../../../common/gamecore/IGridSquareObserver.hpp"

using std::unordered_map;
using std::shared_ptr;
using sf::Drawable;
using sf::Drawable;
using sf::RenderTarget;
using sf::Texture;
using sf::RenderStates;
using sf::Vertex;

class PlayerView;
class GridSquare;
struct Edge;

class GridSquareView : public Drawable, public IGridSquareObserver {
public:
    void OnEdgeOwnerChanged(EdgeOwnerChangedEvent event) override;
    void draw(RenderTarget& target, RenderStates) const override;
    virtual const Texture& GetTexture() const = 0;

protected:
    explicit GridSquareView(Position position, shared_ptr<PlayerView> playerView);

private:
    const Position position;
    unordered_map<Direction, PlayerProxy> currentEdgeOwners;
    const shared_ptr<PlayerView> playerView;

    void DrawGridSquare(RenderTarget& target) const;
    void DrawTexture(const Texture&, RenderTarget&) const;
    void DrawEdge(const Edge& edge, RenderTarget&) const;
    void ColorEdge(Vertex*, const Edge&) const;
    bool EdgeOwnerExists(Direction direction) const;
};


#endif //LORD_OF_THE_SEAS_GRIDSQUAREVIEW_HPP
