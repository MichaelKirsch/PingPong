

#include "Enemy.h"

Enemy::Enemy(sf::Vector2f position, int lifes, float lifetime, sf::Texture *texture, sf::Vector2u imageCount,float switchTime, sf::Vector2u posTile, int nbrTiles) :
        animation(texture,imageCount,switchTime,posTile,nbrTiles)
{
    alive = 1;
    this->Lifetime = lifetime;
    this->LifetimeBegin = lifetime;
    this->Lifes = lifes;
    body.setSize(sf::Vector2f(32.0f,32.0f));
    body.setPosition(position);
    body.setTexture(texture);
}

Enemy::~Enemy() {

}


void Enemy::Update(float deltatime) {
    if(!alive)
        return;
    Lifetime-=deltatime;
    if(Lifetime<=0.0f)
    {
        alive = 0;
        printf("Creature %p died after %f seconds",this,LifetimeBegin);
    }
    else
    {
        animation.Update(deltatime);
        body.setTextureRect(animation.uvRect);
        alive =1;
    }


}

void Enemy::Draw(sf::RenderWindow& window) {
    if(alive)
        window.draw(body);
}

bool Enemy::is_alive() {
    return alive;
}




