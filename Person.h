#pragma  once

#include "SFML/Graphics.hpp"
#include <experimental/random>
#include <iostream>
#define REPRODUCTION_THRESHOLD 30

class Person {
public:
    Person(sf::Vector2f position,int maxAge, int strength,int reproductionBonus);
    ~Person();
    void update();
    sf::Vector3i getColor();
    int getAge(){ return age;};
    int getStrength(){ return strength;};
    bool isAlive(){return alive;};
    void kill();
    int getReproductionValue(){return reproductionValue;};
    bool checkReproduction();
    sf::Vector2f getPosition(){ return position;};
    void setPosition(sf::Vector2f new_position);
private:
    void scan();
    void reproduction();
    int reproductionValue;
    int reproductionBonus;
    sf::Vector2f position;
    bool alive;
    int age;
    int maxAge;
    int strength;
    sf::Vector3i color;
};


