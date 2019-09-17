

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

}

void Game::updateGamestates() {

}

void Game::render() {
    window.clear();
    //all the drawcalls
    window.display();
}



