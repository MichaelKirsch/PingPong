#pragma once

#include <SFML/Graphics.hpp>
class Tile {
public:
    Tile();
    ~Tile();

private:
    sf::Vector2u Tileposition;
    bool has_animation;

protected:
};



