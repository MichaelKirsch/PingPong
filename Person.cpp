
#include "Person.h"

void Person::update() {
    age++;
    reproductionValue++; //the person will age and get more "grown" at every tick

    if(age>maxAge)
    {
        //std::cout << this << "died" << std::endl;
        alive=false;
    }

}

bool Person::checkReproduction() {
    if(reproductionValue>REPRODUCTION_THRESHOLD-reproductionBonus/10)
    {
        return true;
    }
    return false;
}

void Person::kill() {
    alive = false;
}

sf::Vector3i Person::getColor() {
    //the color determines the abilities of the individual person.
    //red == strength
    //green == age
    //blue == reproduction
    return sf::Vector3i(strength, maxAge, reproductionBonus);
}

Person::~Person() {

}

Person::Person(sf::Vector2f position,int maxAge, int strength, int reproductionBonus) {
    //when a person gets generated it will get 255 points. it has to spend at least 30 on every of the three skills strength, reproductionBonus, maxAge.
    //the rest of the points will be set randomly. whenever there is a reproduction there is a slight chance of a shift in its values (mutation)
    createdPersons++;
    alive = true;
    this->position = position;
    this->maxAge = maxAge;
    this->strength = strength;
    this->reproductionBonus=reproductionBonus;
    age = 0;
    reproductionValue = 0;
}

Person::Person(sf::Vector2f position,int maxAge, int strength, int reproductionBonus,bool mutation) {
    //when a person gets generated it will get 255 points. it has to spend at least 30 on every of the three skills strength, reproductionBonus, maxAge.
    //the rest of the points will be set randomly. whenever there is a reproduction there is a slight chance of a shift in its values (mutation)
    createdPersons++;
    alive = true;
    this->position = position;
    this->maxAge = maxAge;
    this->strength = strength;
    this->reproductionBonus=reproductionBonus;
    if(mutation)
    {
        mutate();
    }
    age = 0;
    reproductionValue = 0;
}

void Person::reproduce() {
    reproductionValue = 0;
}

void Person::setPosition(sf::Vector2f new_position) {
    position=new_position;
}

void Person::mutate() {
    strength+=std::experimental::randint(-1,1);
    reproductionBonus+=std::experimental::randint(-1,1);
    maxAge+=std::experimental::randint(-1,1);
}


