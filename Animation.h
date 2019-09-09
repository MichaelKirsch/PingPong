//
// Created by Michael on 09.09.2019.
//

#pragma once


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,sf::Vector2u posTile,int nbrTiles);
    ~Animation();
    void Update(float deltaTime);
    sf::IntRect uvRect;

private:
    sf::Vector2u currentImage;
    sf::Vector2u posTile;
    int nbrTiles;
    float totalTime;
    float switchTime;

protected:
};



