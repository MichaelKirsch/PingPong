//
// Created by Michael on 09.09.2019.
//

#include "Animation.h"


Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;
    uvRect.width = texture->getSize().x /float(imageCount.x);
    uvRect.height= texture->getSize().y /float(imageCount.y);
}

Animation::~Animation()
{

}

void Animation::Update(int row, float deltaTime) {
    currentImage.y = row;
    totalTime +=deltaTime;
    if(totalTime>=switchTime)
    {
        totalTime -=switchTime;
        currentImage.x++;
        if(currentImage.x>=imageCount.x)
        {
            currentImage.x=0;
        }
    }
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
}

void Animation::Update(int row, float deltaTime, int nbrPicsX) {
    currentImage.y = row;
    totalTime +=deltaTime;
    if(totalTime>=switchTime)
    {
        totalTime -=switchTime;
        currentImage.x++;
        if(currentImage.x>=nbrPicsX)
        {
            currentImage.x=0;
        }
    }
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
}

