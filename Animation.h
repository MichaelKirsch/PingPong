//
// Created by Michael on 09.09.2019.
//

#pragma once


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    ~Animation();
    void Update(int row,float deltaTime);
    void Update(int row,float deltaTime,int nbrPicsX);

    sf::IntRect uvRect;

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;

protected:
};



