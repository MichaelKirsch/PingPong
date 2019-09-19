

#pragma once

#include <SFML/Graphics.hpp>
#include "iostream"
#include <vector>
#include <experimental/random>
#include <string>
#include <sstream>
#include <array>
#include "Person.h"
#define WIDTH 1000
#define HEIGHT 1000

#define START_SKILLPOINTS 250
#define SKILL_START 30
#define FRIEND_THRESHOLD 100 //how different can persons be before they will fight

class Game {
    public:
        Game();
        ~Game();
        void run();
    private:
        void spawnColonie(sf::Vector2f pos, int body_Count);
        int getPosInVertexArray(sf::Vector2f position);
        sf::VertexArray tilemap;
        std::vector<Person> entities;
        bool friendDetection(Person person1, Person person2);
        void processEvents();
        void updateGamestates();
        void render();
        void initEntities();
        sf::RenderWindow window;
    protected:
};



