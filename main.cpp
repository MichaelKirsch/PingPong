#include "iostream"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Animation.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(512,512), "PingPong", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
    sf::RectangleShape dude(sf::Vector2f(32.0f,32.0f));
    sf::Texture dudes_texture;
    dudes_texture.loadFromFile("../textures/48x64tileset.png");
    dude.setOrigin(16.0f,16.0f);
    dude.setTexture(&dudes_texture);
    dude.setPosition(50.0f,50.0f);
    Animation animation(&dudes_texture,sf::Vector2u(64,48),0.1f);

    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        sf::Event hapns;
        while (window.pollEvent(hapns))
        {
            switch (hapns.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    printf("Height: %i Width: %i \n",hapns.size.height,hapns.size.width);
                    break;
                case sf::Event::TextEntered:
                    char tx = hapns.text.unicode;
                    if(tx<128) printf("%c",tx);
                        printf("%c",tx);
                    break;
            }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            dude.move(0.0f,-0.1f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            dude.move(-0.1f,0.0f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            dude.move(0.0f,0.1f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            dude.move(0.1f,0.0f);
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i pos =  sf::Mouse::getPosition(window);
            dude.setPosition((float)pos.x,(float)pos.y);
            //dude.setTextureRect(sf::IntRect(texture_size.x*2,texture_size.y*10,texture_size.x,texture_size.y));
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            //dude.setTextureRect(sf::IntRect(texture_size.x*4,texture_size.y*10,texture_size.x,texture_size.y));
        }

        }

        animation.Update(15,deltaTime,5);
        dude.setTextureRect(animation.uvRect);

        window.clear();
        window.draw(dude);
        window.display();

    }
    return EXIT_SUCCESS;
}