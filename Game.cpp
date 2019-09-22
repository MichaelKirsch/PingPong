

#include "Game.h"

Game::Game() : window(sf::VideoMode(WIDTH,HEIGHT),"Automata"){
        window.setFramerateLimit(60);
        tilemap.setPrimitiveType(sf::Points);
        tilemap.resize(WIDTH*HEIGHT);
        grid.resize(WIDTH*HEIGHT);
        std::experimental::reseed(std::default_random_engine::modulus); //TODO scheis random generator zum laufen kriegen
        for(auto& item:grid)
        {
            item = nullptr;
        }


        //make the map "grey" and empty. From there on we will spawn the random colonies
        for(int x = 0;x<grid.size();x++)
        {
                    tilemap[x].position =convertIntPostoVec(x);
                    tilemap[x].color = sf::Color::White;
        }

        spawnColonies(10, 10);

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
    for(int x =0;x<HEIGHT*WIDTH;x++)
    {
        tilemap[x].color = sf::Color::White;
    }
    for(auto& dude:entities)
    {
        dude.update();
        move(dude);
        if(dude.checkReproduction())
        {

            sf::Vector2f newpos = sf::Vector2f(dude.getPosition().x+std::experimental::randint(-1,1),dude.getPosition().y+std::experimental::randint(-1,1));
            if(!collision(newpos))
            {
                dude.reproduce();
                entities.push_back(Person(newpos,dude.getAge(),dude.getStrength(),dude.getreproductionBonus(),
                                          true));
            }

        }
        tilemap[getPosInVertexArray(dude.getPosition())].color = sf::Color(dude.getColor().x,dude.getColor().y,dude.getColor().z);
    }
    for(int x =0;x<entities.size();x++)
    {
        if(!entities[x].isAlive())
        {
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

bool Game::friendDetection(Person *person1, Person *person2) {
    int dif1 = abs(person1->getColor().x - person2->getColor().x);
    int dif2 = abs(person1->getColor().y - person2->getColor().y);
    int dif3 = abs(person1->getColor().z - person2->getColor().z);

    if(dif1+dif2+dif3 > FRIEND_THRESHOLD)
        return false;
    return true;
}

void Game::spawnColonies(int nbrCols, int body_Count) {
    for(int colNbr =0;colNbr<nbrCols;colNbr++)
    {

        sf::Vector2f pos = sf::Vector2f((float)std::experimental::randint((int)(HEIGHT*0.05),(int)HEIGHT),(float)std::experimental::randint((int)(HEIGHT*0.05),(int)HEIGHT));

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
            grid[convertVectoIntPos(position)] = &entities.back();
        }
        std::cout<<"Created Colony at x:" << pos.x << " y:" << pos.y << " with bodycount of " << body_Count << std::endl;
    }

}

int Game::getPosInVertexArray(sf::Vector2f position) {
    return (position.y*HEIGHT)+position.x;
}

bool Game::move(Person& dude) {
    bool collision = false;
    sf::Vector2f newPos=sf::Vector2f(dude.getPosition().x+std::experimental::randint(-1,1),dude.getPosition().y+std::experimental::randint(-1,1));
    if(newPos.y>HEIGHT-2||newPos.y<2||newPos.x>WIDTH-2||newPos.x<2)
        return true;

    if(grid[convertVectoIntPos(newPos)] != nullptr) //If its not a nullptr there is something there
    {
        if(friendDetection(grid[convertVectoIntPos(newPos)],&dude )) //if its a friend then the person will stay put
        {
            //std::cout<<"Position occupied. Friendly!" << std::endl;
            return true; //dont do anything
        }
        if(dude.getStrength()<grid[convertVectoIntPos(newPos)]->getStrength()) //if he clashes with an enemy and looses he will die
        {
            //std::cout << "Position occupied. Enemy! He died" << std::endl;
            return false;
        }
        std::cout<<"1:"<<entities.size()<<std::endl;
        grid[convertVectoIntPos(newPos)]->~Person();
        std::cout<<"2:"<<entities.size()<<std::endl;
        grid[convertVectoIntPos(dude.getPosition())] = nullptr; //where he was standing is now a free space
        grid[convertVectoIntPos(newPos)] = &dude;
        std::cout<<"3:"<<grid[convertVectoIntPos(newPos)]<<std::endl;
        dude.setPosition(newPos);
        //std::cout<<"Position occupied. Enemy! He survived" << std::endl;
        return true;
        }
    }


bool Game::collision(sf::Vector2f newPos) {
    if(newPos.x>WIDTH-2||newPos.x<2||newPos.y>HEIGHT-2||newPos.y<2)
        return false;
    for(auto& dudes:entities)
    {
        if(dudes.getPosition()==newPos)
        {
            return false;
        }
    }
    return true;
}

sf::Vector2f Game::convertIntPostoVec(int position) {
    int y = position/HEIGHT;
    int x = position%HEIGHT;
    return sf::Vector2f(x,y);
}

int Game::convertVectoIntPos(sf::Vector2f position) {
    return position.x*position.y;
}












