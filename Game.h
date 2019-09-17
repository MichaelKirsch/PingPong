

#pragma once

#include <SFML/Graphics.hpp>
#include "iostream"
#include <vector>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include <experimental/random>
#include "Enemy.h"
#include <string>
#include <sstream>


class Game {
    public:
        Game();
        ~Game();
        void run();
    private:
        void processEvents();
        void updateGamestates();
        void render();
        void initEntities();

        sf::RenderWindow window;
    protected:
};



