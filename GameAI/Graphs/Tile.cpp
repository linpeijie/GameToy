#include "includes/Tile.h"

// 初始化，默认ID：empty，需传入IntRect变量
Tile::Tile(sf::IntRect intrect, tile::ID ID):
                rect(sf::Vector2f(intrect.width, intrect.height)),
                id(ID)
{
    rect.setFillColor(IDtoColor(id));
    rect.setPosition(intrect.left, intrect.top);

    rect.setOutlineColor(sf::Color(160, 160, 160));
    rect.setOutlineThickness(0.6f);

    x = intrect.left / intrect.width;
    y = intrect.top / intrect.height;
}

// 绘制图形
void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(rect, states);
}

// 返回 tile 在二维矩阵中的索引，
sf::Vector2i Tile::getIndex()
{
    return sf::Vector2i(x, y);
}

void Tile::setID(tile::ID id)
{
    this->id = id;
    rect.setFillColor(IDtoColor(id));
}

tile::ID Tile::getID() const
{
    return id;
}

// 将标签转为对应的颜色
sf::Color Tile::IDtoColor(tile::ID id)
{
    switch (id)
    {
    case tile::Empty:
        return sf::Color::White;
        break;
    case tile::Path:
        return sf::Color::Blue;
        break;
    case tile::Start:
        return sf::Color::Yellow;
        break;
    case tile::End:
        return sf::Color::Red;
        break;
    case tile::SearchPath:
        return sf::Color::Green;
        break;
    default:
        return sf::Color::Black;
        break;
    }
}
