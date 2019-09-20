

#pragma once

#include <SFML/Graphics.hpp>
#include "iostream"
#include <vector>
#include <experimental/random>
#include <string>
#include <sstream>
#include <array>
#include "Person.h"
#include <random>
#include <chrono>


#define WIDTH 1000
#define HEIGHT 1000

#define START_SKILLPOINTS 250
#define SKILL_START 30
#define FRIEND_THRESHOLD 50 //how different can persons be before they will fight

class Game {
    //VARS
    public:
        Game();
        ~Game();
    private:
        sf::RenderWindow window;
        std::vector<Person *>grid;
        sf::VertexArray tilemap;
        std::vector<Person> entities;
    //FUNCTIONS
    public:
        void run();
    private:
        bool collision(sf::Vector2f newPos);
        sf::Vector2f convertIntPostoVec(int position);
        int convertVectoIntPos(sf::Vector2f position);
        void spawnColonies(int nbrCols, int body_Count);
        int getPosInVertexArray(sf::Vector2f position);
        bool friendDetection(Person person1, Person person2);
        void processEvents();
        void updateGamestates();
        void render();
        bool move(Person& dude);
    };



