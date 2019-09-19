

#include "Game.h"

Game::Game() : window(sf::VideoMode(WIDTH,HEIGHT),"Automata"){
    //window.setFramerateLimit(60);

    tilemap.setPrimitiveType(sf::Points);
    tilemap.resize(WIDTH*HEIGHT);
    int counter=0;
    for(int x=0;x<=WIDTH-1;x++)
    {
        for (int y=0;y<=HEIGHT-1;y++)
            {
                counter++;
                tilemap[counter].position = sf::Vector2f((float)x, (float)y);
                tilemap[counter].color = sf::Color(50,50,50);
            }
    }
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
    window.draw(tilemap);
    window.display();
}




