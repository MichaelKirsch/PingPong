#include "iostream"
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Enemy.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(512,512), "PointNClick", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
    sf::RectangleShape dude(sf::Vector2f(32.0f,32.0f));
    sf::Texture dudes_texture;
    dudes_texture.loadFromFile("../textures/48x64tileset.png");
    dude.setOrigin(16.0f,16.0f);
    dude.setTexture(&dudes_texture);

    dude.setPosition(50.0f,50.0f);
    Animation animation(&dudes_texture,sf::Vector2u(64,48),0.1f,sf::Vector2u(58,18),3);
    std::vector<sf::RectangleShape> allthetiles;
    Enemy enemy(sf::Vector2f(100.0f,100.0f),3,4.0f,&dudes_texture,sf::Vector2u(64,48),0.1f,sf::Vector2u(58,18),3);
    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        sf::Event hapns;
        while (window.pollEvent(hapns)) {
                if (hapns.type==sf::Event::Closed)
                    window.close();

            }
        enemy.Update(deltaTime);
        sf::Vector2i pos =  sf::Mouse::getPosition(window);
        dude.setPosition((float)pos.x,(float)pos.y);
        animation.Update(deltaTime);
        dude.setTextureRect(animation.uvRect);

        window.clear();
        enemy.Draw(window);
        window.draw(dude);
        window.display();

    }
    return EXIT_SUCCESS;
}