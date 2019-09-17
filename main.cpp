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
    sf::RenderWindow window(sf::VideoMode(1000,1000), "PointNClick", sf::Style::Titlebar | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f,0.0f),sf::Vector2f(1000.0f,1000.0f));
    sf::RectangleShape dude(sf::Vector2f(32.0f,32.0f));
    sf::Texture dudes_texture;
    sf::Texture ship;
    sf::Font font;
    if (!font.loadFromFile("../fonts/california.ttf"))
        return EXIT_FAILURE;
    dudes_texture.loadFromFile("../textures/48x64tileset.png");
    ship.loadFromFile("../textures/Zweimaast.png");
    dude.setOrigin(16.0f,16.0f);
    dude.setTexture(&ship);

    std::vector<Enemy> lifestock;
    dude.setPosition(view.getCenter());
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
                else if(hapns.type == sf::Event::MouseWheelMoved)
                {
                    view.setSize(view.getSize().x+hapns.mouseWheel.delta*100.0f,view.getSize().y+hapns.mouseWheel.delta*100.0f);
                }
            }
        sf::Vector2i pos =  sf::Mouse::getPosition(window);

        //position is between 0,0 and windowsize
        //whenever the mouse is at one border i want the view to be adjusted
        //the threshold for that is 5%
        float threshold = 0.05;
        float scroll_speed = 0.2f;
        float threshold_x = window.getSize().x*threshold;
        float threshold_y = window.getSize().y*threshold;
        if(pos.x < threshold_x || pos.x > window.getSize().x-threshold_x)
        {
            sf::Vector2f old_center = view.getCenter();
            if(pos.x < threshold_x)
            {
                view.setCenter(old_center.x-scroll_speed,old_center.y);
            }
            if(pos.x > window.getSize().x-threshold_x)
            {
                view.setCenter(old_center.x+scroll_speed,old_center.y);
            }

        }
        if(pos.y < threshold_y || pos.y > window.getSize().y-threshold_y)
        {
            sf::Vector2f old_center = view.getCenter();
            if(pos.y < threshold_y)
            {
                view.setCenter(old_center.x,old_center.y-scroll_speed);
            }
            if(pos.y > window.getSize().x-threshold_y)
            {
                view.setCenter(old_center.x,old_center.y+scroll_speed);
            }
        }
        dude.setPosition(view.getCenter().x+sf::Mouse::getPosition(window).x,view.getCenter().y+sf::Mouse::getPosition(window).y);

        animation.Update(deltaTime);
        //dude.setTextureRect(animation.uvRect);

        window.setView(view);

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
        dude.setTexture(&ship);
        window.draw(dude);
        window.draw(text);
        window.display();

    }
    return EXIT_SUCCESS;
}

