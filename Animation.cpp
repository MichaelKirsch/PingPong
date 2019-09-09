//
// Created by Michael on 09.09.2019.
//

#include "Animation.h"


Animation::Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime, sf::Vector2u posTile,int nbrTiles) {
    this->switchTime = switchTime;
    this->posTile = posTile;
    this->nbrTiles = nbrTiles;
    totalTime = 0.0f;
    currentImage.y = posTile.y;
    currentImage.x = posTile.x;
    uvRect.width = texture->getSize().x /float(imageCount.x);
    uvRect.height= texture->getSize().y /float(imageCount.y);
}



Animation::~Animation()
{

}

void Animation::Update(float deltaTime) {

    totalTime +=deltaTime;
    if(totalTime>=switchTime)
    {
        totalTime-=switchTime;
        currentImage.x++;
        if(currentImage.x>=posTile.x+nbrTiles)
        {
            currentImage.x=posTile.x;
        }
    }
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
}




