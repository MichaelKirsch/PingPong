#include "iostream"
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <experimental/random>
#include "Enemy.h"
#include <string>
#include <sstream>

int main() {
    int creaturesTotal = 0;
    sf::RenderWindow window(sf::VideoMode(1000,1000), "PointNClick", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close );
    sf::RectangleShape dude(sf::Vector2f(32.0f,32.0f));
    sf::Texture dudes_texture;
    sf::Font font;
    if (!font.loadFromFile("../fonts/california.ttf"))
        return EXIT_FAILURE;
    dudes_texture.loadFromFile("../textures/48x64tileset.png");
    dude.setOrigin(16.0f,16.0f);
    dude.setTexture(&dudes_texture);

    std::vector<Enemy> lifestock;
    dude.setPosition(50.0f,50.0f);
    Animation animation(&dudes_texture,sf::Vector2u(64,48),0.1f,sf::Vector2u(58,18),3);
    std::vector<sf::RectangleShape> allthetiles;
    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        sf::Event hapns;
        while (window.pollEvent(hapns)) {
                if (hapns.type==sf::Event::Closed)
                    window.close();
                if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                    creaturesTotal++;
                    float anim_time = std::experimental::randint(10,200)/100.0;
                    sf::Vector2u sprite = sf::Vector2u(12,18);
                    sf::Vector2f pos = sf::Vector2f((float)sf::Mouse::getPosition(window).x,(float)sf::Mouse::getPosition(window).y);
                    float lifetime = (float)std::experimental::randint(100,2000)/100.0;
                    Enemy placeholder(pos,3,lifetime,&dudes_texture,sf::Vector2u(64,48),anim_time,sprite,3);
                    lifestock.push_back(placeholder);
                }
            }
        sf::Vector2i pos =  sf::Mouse::getPosition(window);
        dude.setPosition((float)pos.x,(float)pos.y);
        animation.Update(deltaTime);
        dude.setTextureRect(animation.uvRect);

        window.clear();
        for(int x =0;x<lifestock.size();x++)
        {
            if(!lifestock[x].is_alive())
            {
                lifestock.erase(lifestock.begin()+x); //delete the unnecessary entries of the vector
            }
            lifestock[x].Update(deltaTime);
            lifestock[x].Draw(window);
        }
        std::ostringstream ss;
        ss << "Creatures alive:" << lifestock.size() << "\nCreatures ever:"<< creaturesTotal<<"\nCreatures dead:"<<creaturesTotal-lifestock.size();
        sf::Text text(ss.str(), font, 20);
        window.draw(dude);
        window.draw(text);
        window.display();

    }
    return EXIT_SUCCESS;
}

