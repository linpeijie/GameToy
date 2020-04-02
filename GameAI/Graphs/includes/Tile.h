#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <SFML/Graphics.hpp>

namespace tile
{
    enum ID
    {
        Start, End, Path, Empty, Wall, SearchPath
    };
}

class Tile: public sf::Drawable, public sf::Transformable
{
private:
    int x;
    int y;

    sf::RectangleShape rect;
    tile::ID id;
    // 不同id对应不同颜色
    static sf::Color IDtoColor(tile::ID id);

public:
    Tile() {}
    ~Tile() {}
    // 取消隐式转换
    explicit Tile(sf::IntRect intrect, tile::ID id = tile::Empty);

    sf::Vector2i getIndex();
    void setID(tile::ID id);
    tile::ID getID() const;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif