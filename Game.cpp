

#include "Game.h"

Game::Game() : window(sf::VideoMode(800,600),"This Game is awesome"){
    window.setFramerateLimit(60);

}

Game::~Game() {

}

void Game::run() {
    while(window.isOpen())
    {
        processEvents();
        updateGamestates();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
        }
    }
}

void Game::updateGamestates() {
}

void Game::render() {
    window.clear();
    //all the drawcalls
    window.display();
}

void Game::initEntities() {

}



