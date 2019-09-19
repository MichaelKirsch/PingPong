

#pragma once

#include <SFML/Graphics.hpp>
#include "iostream"
#include <vector>
#include <experimental/random>
#include <string>
#include <sstream>
#include <array>

#define WIDTH 1000
#define HEIGHT 1000

class Game {
    public:
        Game();
        ~Game();
        void run();
    private:
        sf::VertexArray tilemap;
        void processEvents();
        void updateGamestates();
        void render();
        void initEntities();
        sf::RenderWindow window;
    protected:
};



