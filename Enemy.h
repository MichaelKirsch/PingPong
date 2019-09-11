

#pragma once

#include "Animation.h"
#include "SFML/Graphics.hpp"

class Enemy {
public:
    Enemy(sf::Vector2f position, int lifes, float lifetime,sf::Texture *texture, sf::Vector2u imageCount, float switchTime, sf::Vector2u posTile,int nbrTiles);
    void Draw(sf::RenderWindow& window);
    void Update(float deltatime);
    bool is_alive();
    ~Enemy();

private:
    sf::RectangleShape body;
    Animation animation;
    int Lifes;
    float LifetimeBegin;
    float Lifetime;
    bool alive;
protected:
};



