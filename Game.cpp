

#include "Game.h"

Game::Game() : window(sf::VideoMode(WIDTH,HEIGHT),"Automata"){
    window.setFramerateLimit(60);
    tilemap.setPrimitiveType(sf::Points);
    tilemap.resize(WIDTH*HEIGHT);


    int counter=0;
    //make the map "grey" and empty. From there on we will spawn the random colonies
    for (int y=0;y<=HEIGHT-1;y++)
    {
        for(int x=0;x<=WIDTH-1;x++)
            {
                counter++;
                tilemap[counter].position = sf::Vector2f((float)x, (float)y);
                tilemap[counter].color = sf::Color(50,50,50);
            }
    }

    for(int nbrcol =0;nbrcol<10;nbrcol++)
    {
        spawnColonie(sf::Vector2f((float)std::experimental::randint(200,HEIGHT-200),(float)std::experimental::randint(200,WIDTH-200)),40);
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
    for(int x =0;x<entities.size();x++)
    {
        entities[x].update();
        move(entities[x]);
        if(entities[x].checkReproduction())
        {
            entities[x].reproduce();
            sf::Vector2f newpos = sf::Vector2f(entities[x].getPosition().x+std::experimental::randint(5-10,10),entities[x].getPosition().y+std::experimental::randint(-10,10));
            entities.push_back(Person(newpos,entities[x].getAge(),entities[x].getStrength(),entities[x].getreproductionBonus()));
        }

        int red = entities[x].getColor().x;
        int green = entities[x].getColor().y;
        int blue = entities[x].getColor().z;
        tilemap[getPosInVertexArray(entities[x].getPosition())].color = sf::Color(red,green,blue);
    }

    for(int x =0;x<entities.size();x++)
    {
        if(!entities[x].isAlive())
        {
            tilemap[getPosInVertexArray(entities[x].getPosition())].color = sf::Color(50,50,50);
            entities.erase(entities.begin()+x);
        }
    }
    std::cout<< "Entities: " << entities.size() <<std::endl;
}

void Game::render() {
    window.clear();
    window.draw(tilemap);
    window.display();
}

bool Game::friendDetection(Person person1, Person person2) {
    int dif1 = abs(person1.getColor().x - person2.getColor().x);
    int dif2 = abs(person1.getColor().y - person2.getColor().y);
    int dif3 = abs(person1.getColor().z - person2.getColor().z);

    if(dif1+dif2+dif3 > FRIEND_THRESHOLD)
        return false;
    return true;

}

void Game::spawnColonie(sf::Vector2f pos, int body_Count) {

        int maxAge = SKILL_START;
        int reproductionBonus = SKILL_START;
        int strength = SKILL_START;

        int restofthepoints = START_SKILLPOINTS-(maxAge+reproductionBonus+strength);

        int first_stage = restofthepoints-std::experimental::randint(0,restofthepoints);
        int second_stage = first_stage-std::experimental::randint(0,first_stage);
        int third_stage = second_stage-std::experimental::randint(0,second_stage);

        maxAge+=first_stage;
        reproductionBonus+=second_stage;
        strength+=third_stage;
    for(int x =0;x<body_Count;x++)
    {
        sf::Vector2f position = sf::Vector2f(pos.x+body_Count,pos.y+std::experimental::randint(0,body_Count));
        entities.push_back(Person(position ,maxAge,strength,reproductionBonus));
    }
    std::cout<<"Created Colonie at x:" << pos.x << " y:" << pos.y << " with bodycount of " << body_Count << std::endl;
}

int Game::getPosInVertexArray(sf::Vector2f position) {
    return (position.y*HEIGHT)+position.x;
}

bool Game::move(Person& dude) {
    bool collision = false;
    sf::Vector2f newPos=sf::Vector2f(dude.getPosition().x+std::experimental::randint(-1,1),dude.getPosition().y+std::experimental::randint(-1,1));
    if(newPos.y>HEIGHT||newPos.y<0||newPos.x>WIDTH||newPos.x<0)
        return true;
    for(auto& value: entities) {
        if(value.getPosition()==newPos)
        {
            if(friendDetection(value,dude))
            {
                //stay put
                return true;
            }
            if(value.getStrength()>dude.getStrength())
            {
                return false;
            }
            else
            {
                dude.setPosition(newPos);
                value.kill();
                return true;
            }
        }
    }
    dude.setPosition(newPos);
    return true;
}







